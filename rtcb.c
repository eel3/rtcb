/* ********************************************************************** */
/**
 * @brief    rtcb; Read Text from ClipBoard
 * @author   eel3
 * @date     2014/09/18
 *
 * @par OS:
 *   - Microsoft Windows XP Professional (32bit) SP3
 *   - Microsoft Windows 7 (64bit) SP1
 *
 * @par Compilers:
 *   - Microsoft(R) Visual Studio 2005 SP1
 *   - Microsoft(R) Visual Studio 2010 SP1
 *   - TDM-GCC 4.8.1
 */
/* ********************************************************************** */


#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <io.h>
#include <tchar.h>
#include <windows.h>

#ifndef STDIN_FILENO
#	define STDIN_FILENO 0
#endif
#ifndef STDOUT_FILENO
#	define STDOUT_FILENO 1
#endif

#if defined(__MINGW32__) || defined(__MINGW64__)
#	ifndef _tperror
#		ifdef UNICODE
#			define _tperror _wperror
#		else
#			define _tperror perror
#		endif
#	endif
	typedef DWORD GS_SIZE_T;
#else
	typedef SIZE_T GS_SIZE_T;
#endif


/* ---------------------------------------------------------------------- */
/* Function */
/* ---------------------------------------------------------------------- */

/* ====================================================================== */
/**
 * @brief  Pring error message and exit application.
 *
 * @param[in] s           header message of error.
 * @param[in] last_error  error code
 */
/* ====================================================================== */
static void
error_exit(const LPCTSTR s, const DWORD last_error)
{
	LPTSTR buf;

	assert(s != NULL);

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER
	              | FORMAT_MESSAGE_IGNORE_INSERTS
	              | FORMAT_MESSAGE_FROM_SYSTEM,
	              NULL,
	              last_error,
	              MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	              (LPTSTR) &buf,
	              0,
	              NULL);

	_ftprintf(stderr, _T("%s: %s"), s, buf);
	LocalFree((HLOCAL) buf);

	exit(EXIT_FAILURE);
}

/* ********************************************************************** */
/**
 * @brief  Main routine.
 *
 * @retval EXIT_SUCCESS  OK (success).
 * @retval EXIT_FAILURE  NG (failure).
 */
/* ********************************************************************** */
int
main(void)
{
#define ERREXIT(s)                  \
	DWORD err = GetLastError();     \
	(void) CloseClipboard();        \
	error_exit(_T(s), err);

	HANDLE hMem;
	LPVOID p;
	GS_SIZE_T size;

	errno = 0;
	if (_setmode(STDOUT_FILENO, O_BINARY) == -1) {
		_tperror(_T("_setmode"));
		return EXIT_FAILURE;
	}

	if (!OpenClipboard(NULL)) {
		error_exit(_T("OpenClipboard"), GetLastError());
	}

	if (!IsClipboardFormatAvailable(CF_OEMTEXT)) {
		ERREXIT("IsClipboardFormatAvailable");
	}

	if ((hMem = GetClipboardData(CF_OEMTEXT)) == NULL) {
		ERREXIT("GetClipboardData");
	}

	if ((p = GlobalLock(hMem)) == NULL) {
		ERREXIT("GlobalLock");
	}

	if ((size = GlobalSize(hMem)) > 1) {
		/* do not write ASCII NUL. */
		(void) fwrite(p, size - 1, 1, stdout);
	}

	(void) GlobalUnlock(hMem);
	(void) CloseClipboard();

	return EXIT_SUCCESS;

#undef ERREXIT
}
