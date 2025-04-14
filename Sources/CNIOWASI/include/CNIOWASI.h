//===----------------------------------------------------------------------===//
//
// This source file is part of the SwiftNIO open source project
//
// Copyright (c) YEARS Apple Inc. and the SwiftNIO project authors
// Licensed under Apache License v2.0
//
// See LICENSE.txt for license information
// See CONTRIBUTORS.txt for the list of SwiftNIO project authors
//
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//

// TODO: SM: Find all places I'm using this and see if import wasilibc will work instead. Should default to that first

// TODO: SM: Make a pass through all the CNIOLinux usages and make sure I'm not missing some #if changes anywhere

// TODO: SM: See if any unit test can be enabled, figure out how to compile and run them.

// TODO: SM: Make usage readme for wasm usage (with compiler flags) and table of what works and what doesn't in wasm builds.

#ifndef C_NIO_WASI_H
#define C_NIO_WASI_H

#if __wasi__

#include <sys/socket.h>
#include <fcntl.h>
#include <time.h>

#include <pthread.h>
#include <threads.h>
#include <sched.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <limits.h>
#include <bits/dirent.h>
#include <bits/signal.h>

// TODO: SM: Remove notes about importable headers below

// // All below (c posix lib) compiles with 0.2
// #include <assert.h>
// #include <complex.h>
// #include <ctype.h>
// #include <dirent.h>
// #include <dlfcn.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <fenv.h>
// #include <float.h>
// #include <inttypes.h>
// #include <iso646.h>
// #include <limits.h>
// #include <locale.h>
// #include <math.h>
// #include <pthread.h>
// // #include <setjmp.h> // No in WASI 0.2
// // #include <signal.h> // No in WASI 0.2, but there is emulated signal support
// #include <stdarg.h>
// #include <stdbool.h>
// #include <stddef.h>
// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/stat.h>
// #include <tgmath.h>
// #include <time.h>
// #include <unistd.h>
// #include <utime.h>
// #include <wchar.h>
// #include <wctype.h>
// 
// #include <sys/socket.h>

// // All below (c posix lib) compiles with 0.2
// // #include <aio.h>
// #include <arpa/inet.h>
// #include <assert.h>
// #include <complex.h>
// #include <cpio.h>
// #include <ctype.h>
// #include <dirent.h>
// #include <dlfcn.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <fenv.h>
// #include <float.h>
// #include <fmtmsg.h>
// #include <fnmatch.h>
// #include <ftw.h>
// #include <glob.h>
// // #include <grp.h> // No
// #include <iconv.h>
// #include <inttypes.h>
// #include <iso646.h>
// #include <langinfo.h>
// #include <libgen.h>
// #include <limits.h>
// #include <locale.h>
// #include <math.h>
// #include <monetary.h>
// #include <mqueue.h>
// // #include <ndbm.h> // No
// // #include <net/if.h> // No
// // #include <netdb.h> // No
// #include <netinet/in.h>
// #include <netinet/tcp.h>
// #include <nl_types.h>
// #include <poll.h>
// #include <pthread.h>
// // #include <pwd.h> // No
// #include <regex.h>
// #include <sched.h>
// #include <search.h>
// #include <semaphore.h>
// // #include <setjmp.h> // No
// // #include <signal.h> // No
// // #include <spawn.h> // No
// #include <stdarg.h>
// #include <stdbool.h>
// #include <stddef.h>
// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <strings.h>
// #include <stropts.h>
// // #include <sys/ipc.h> // No
// // #include <sys/mman.h> // No
// // #include <sys/msg.h> // No
// // #include <sys/resource.h> // No
// #include <sys/select.h>
// // #include <sys/sem.h> // No
// // #include <sys/shm.h> // No
// #include <sys/socket.h>
// #include <sys/stat.h>
// #include <sys/statvfs.h>
// #include <sys/time.h>
// // #include <sys/times.h> // No
// #include <sys/types.h>
// #include <sys/uio.h>
// #include <sys/un.h>
// #include <sys/utsname.h>
// // #include <sys/wait.h> // No
// // #include <syslog.h> // No
// #include <tar.h>
// // #include <termios.h> // No
// #include <tgmath.h>
// #include <time.h>
// // #include <trace.h> // No
// // #include <ulimit.h> // No
// #include <unistd.h>
// #include <utime.h>
// // #include <utmpx.h> // No
// #include <wchar.h>
// #include <wctype.h>
// // #include <wordexp.h> // No



// // All below (c posix lib) compiles with 0.1
// #include <assert.h>
// #include <complex.h>
// #include <ctype.h>
// #include <dirent.h>
// #include <dlfcn.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <fenv.h>
// #include <float.h>
// #include <inttypes.h>
// #include <iso646.h>
// #include <limits.h>
// #include <locale.h>
// #include <math.h>
// #include <pthread.h>
// // #include <setjmp.h> // No in WASI 0.1
// // #include <signal.h> // No in WASI 0.1
// #include <stdarg.h>
// #include <stdbool.h>
// #include <stddef.h>
// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/stat.h>
// #include <tgmath.h>
// #include <time.h>
// #include <unistd.h>
// #include <utime.h>
// #include <wchar.h>
// #include <wctype.h>
// 
// #include <sys/socket.h> // No in WASI 0.1

// // All below (c posix lib) compiles with 0.1
// // #include <aio.h> // No
// #include <arpa/inet.h>
// #include <assert.h>
// #include <complex.h>
// #include <cpio.h>
// #include <ctype.h>
// #include <dirent.h>
// #include <dlfcn.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <fenv.h>
// #include <float.h>
// #include <fmtmsg.h>
// #include <fnmatch.h>
// #include <ftw.h>
// #include <glob.h>
// // #include <grp.h> // No
// #include <iconv.h>
// #include <inttypes.h>
// #include <iso646.h>
// #include <langinfo.h>
// #include <libgen.h>
// #include <limits.h>
// #include <locale.h>
// #include <math.h>
// #include <monetary.h>
// #include <mqueue.h>
// // #include <ndbm.h> // No
// // #include <net/if.h> // No
// // #include <netdb.h> // No
// #include <netinet/in.h>
// #include <netinet/tcp.h>
// #include <nl_types.h>
// #include <poll.h>
// #include <pthread.h>
// // #include <pwd.h> // No
// #include <regex.h>
// #include <sched.h>
// #include <search.h>
// #include <semaphore.h>
// // #include <setjmp.h> // No
// // #include <signal.h> // No
// // #include <spawn.h> // No
// #include <stdarg.h>
// #include <stdbool.h>
// #include <stddef.h>
// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <strings.h>
// #include <stropts.h>
// // #include <sys/ipc.h> // No
// // #include <sys/mman.h> // No
// // #include <sys/msg.h> // No
// // #include <sys/resource.h> // No
// #include <sys/select.h>
// // #include <sys/sem.h> // No
// // #include <sys/shm.h> // No
// #include <sys/socket.h>
// #include <sys/stat.h>
// #include <sys/statvfs.h>
// #include <sys/time.h>
// // #include <sys/times.h> // No
// #include <sys/types.h>
// #include <sys/uio.h>
// #include <sys/un.h>
// #include <sys/utsname.h>
// // #include <sys/wait.h> // No
// // #include <syslog.h> // No
// #include <tar.h>
// // #include <termios.h> // No
// #include <tgmath.h>
// #include <time.h>
// // #include <trace.h> // No
// // #include <ulimit.h> // No
// #include <unistd.h>
// #include <utime.h>
// // #include <utmpx.h> // No
// #include <wchar.h>
// #include <wctype.h>
// // #include <wordexp.h> // No




// foo

// TODO: Figure out how to get WASI_EMULATED_SIGNAL to compile. The .a lib is there in the swift wasm wasilibc
// Once this is figured out, `BaseSocketProtocol.ignoreSIGPIPE` can be implemented.
// #include <signal.h>

static inline void CNIOWASI_gettime(struct timespec *tv) {
    // ClangImporter doesn't support `CLOCK_MONOTONIC` declaration in WASILibc, thus we have to define a bridge manually
    clock_gettime(CLOCK_MONOTONIC, tv);
}

static inline int CNIOWASI_O_CREAT() {
    // ClangImporter doesn't support `O_CREATE` declaration in WASILibc, thus we have to define a bridge manually
    return O_CREAT;
}

// Some explanation is required here.
//
// Due to SR-6772, we cannot get Swift code to directly see any of the mmsg structures or
// functions. However, we *can* get C code built by SwiftPM to see them. For this reason we
// elect to provide a selection of shims to enable Swift code to use recv_mmsg and send_mmsg.
// Mostly this is fine, but to minimise the overhead we want the Swift code to be able to
// create the msgvec directly without requiring further memory fussiness in our C shim.
// That requires us to also construct a C structure that has the same layout as struct mmsghdr.
//
// Conveniently glibc has pretty strict ABI stability rules, and this structure is part of the
// glibc ABI, so we can just reproduce the structure definition here and feel confident that it
// will be sufficient.
//
// If SR-6772 ever gets resolved we can remove this shim.
//
// https://bugs.swift.org/browse/SR-6772

// https://github.com/WebAssembly/wasi-libc/blob/09683b3623ec49f79899fc1d847f29e26af80fd1/libc-top-half/musl/include/sys/socket.h#L71
typedef struct {
    struct msghdr msg_hdr;
    unsigned int msg_len;
} CNIOWASI_mmsghdr;


// NOTE: Scott Marchant, March 26, 2025:
//
// The following struct is elided by a #ifdef __wasilibc_unmodified_upstream in socket.h.
// For now, we're just copy-pasting these definitions since there doesn't appear to be an
// actual limitation in the WASI spec prohibiting the definition of this message structure.

// Begin copy-paste-adapation
struct cmsghdr {
	socklen_t cmsg_len;
	int cmsg_level;
	int cmsg_type;
};
// End copy-paste

int CNIOWASI_sendmmsg(int sockfd, CNIOWASI_mmsghdr *msgvec, unsigned int vlen, unsigned int flags);
int CNIOWASI_recvmmsg(int sockfd, CNIOWASI_mmsghdr *msgvec, unsigned int vlen, unsigned int flags, struct timespec *timeout);

const char* CNIOWASI_dirent_dname(struct dirent* ent);

// FCNTL bit-field define passthroughs
extern const int CNIOWASI_O_APPEND;
extern const int CNIOWASI_O_SYNC;
extern const int CNIOWASI_O_NONBLOCK;

// Socket option passthroughs
extern const int CNIOWASI_SO_REUSEADDR;
extern const int CNIOWASI_SO_ERROR;
extern const int CNIOWASI_SO_SNDBUF;
extern const int CNIOWASI_SO_RCVBUF;
extern const int CNIOWASI_SO_KEEPALIVE;
extern const int CNIOWASI_SO_ACCEPTCONN;
extern const int CNIOWASI_SO_PROTOCOL;
extern const int CNIOWASI_SO_DOMAIN;
extern const int CNIOWASI_SO_RCVTIMEO;

extern const int CNIOWASI_SOCK_DGRAM;
extern const int CNIOWASI_SOCK_STREAM;

// cmsghdr handling
struct cmsghdr *CNIOWASI_CMSG_FIRSTHDR(const struct msghdr *);
struct cmsghdr *CNIOWASI_CMSG_NXTHDR(struct msghdr *, struct cmsghdr *);
const void *CNIOWASI_CMSG_DATA(const struct cmsghdr *);
void *CNIOWASI_CMSG_DATA_MUTABLE(struct cmsghdr *);
size_t CNIOWASI_CMSG_LEN(size_t);
size_t CNIOWASI_CMSG_SPACE(size_t);

#endif // __wasi__
#endif // C_NIO_WASI_H
