//===----------------------------------------------------------------------===//
//
// This source file is part of the SwiftNIO open source project
//
// Copyright (c) 2025 Apple Inc. and the SwiftNIO project authors
// Licensed under Apache License v2.0
//
// See LICENSE.txt for license information
// See CONTRIBUTORS.txt for the list of SwiftNIO project authors
//
// SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------===//

// Xcode's Archive builds with Xcode's Package support struggle with empty .c files
// (https://bugs.swift.org/browse/SR-12939).
void CNIOWASI_i_do_nothing_just_working_around_a_darwin_toolchain_bug(void) {}

#if __wasi__

// SM: make sure gnu_source is defined

#ifndef _GNU_SOURCE
#error You must define _GNU_SOURCE
#endif

#include <CNIOWASI.h>

// SM: better to import here than in the header. Otherwise you get dependency soup

// #include <pthread.h>
// #include <sched.h>
// #include <stdio.h>
// #include <sys/syscall.h>
// #include <sys/utsname.h>
// #include <unistd.h>
// #include <assert.h>
// #include <time.h>
// #include <sys/ioctl.h>
// #include <sys/stat.h>
#include <sys/socket.h>

_Static_assert(sizeof(CNIOWASI_mmsghdr) == sizeof(struct mmsghdr),
               "sizes of CNIOWASI_mmsghdr and struct mmsghdr differ");

int CNIOWASI_sendmmsg(int sockfd, CNIOWASI_mmsghdr *msgvec, unsigned int vlen, unsigned int flags) {
    return sendmmsg(sockfd, (struct mmsghdr *)msgvec, vlen, flags);
}

int CNIOWASI_recvmmsg(int sockfd, CNIOWASI_mmsghdr *msgvec, unsigned int vlen, unsigned int flags, struct timespec *timeout) {
    return recvmmsg(sockfd, (struct mmsghdr *)msgvec, vlen, flags, timeout);
}

const char* CNIOWASI_dirent_dname(struct dirent* ent) {
    return ent->d_name;
}

// FCNTL bit-field define passthroughs
const int CNIOWASI_O_APPEND = O_APPEND;
const int CNIOWASI_O_SYNC = O_SYNC;
const int CNIOWASI_O_NONBLOCK = O_NONBLOCK;

// Socket options passthrough
const int CNIOWASI_SO_REUSEADDR = SO_REUSEADDR;
const int CNIOWASI_SO_ERROR = SO_ERROR;
const int CNIOWASI_SO_SNDBUF = SO_SNDBUF;
const int CNIOWASI_SO_RCVBUF = SO_RCVBUF;
const int CNIOWASI_SO_KEEPALIVE = SO_KEEPALIVE;
const int CNIOWASI_SO_ACCEPTCONN = SO_ACCEPTCONN;
const int CNIOWASI_SO_PROTOCOL = SO_PROTOCOL;
const int CNIOWASI_SO_DOMAIN = SO_DOMAIN;
const int CNIOWASI_SO_RCVTIMEO = SO_RCVTIMEO;

const int CNIOWASI_SOCK_DGRAM = SOCK_DGRAM;
const int CNIOWASI_SOCK_STREAM = SOCK_STREAM;

// NOTE: Scott Marchant, March 26, 2025:
//
// The following are elided by a #ifdef __wasilibc_unmodified_upstream in socket.h.
// For now, we're just copy-pasting these definitions since there doesn't appear to be an
// actual limitation in the WASI spec prohibiting the definition of this message structure.

// Begin copy-paste
#define __CMSG_LEN(cmsg) (((cmsg)->cmsg_len + sizeof(long) - 1) & ~(long)(sizeof(long) - 1))
#define __CMSG_NEXT(cmsg) ((unsigned char *)(cmsg) + __CMSG_LEN(cmsg))
#define __MHDR_END(mhdr) ((unsigned char *)(mhdr)->msg_control + (mhdr)->msg_controllen)

#define CMSG_DATA(cmsg) ((unsigned char *) (((struct cmsghdr *)(cmsg)) + 1))
#define CMSG_NXTHDR(mhdr, cmsg) ((cmsg)->cmsg_len < sizeof (struct cmsghdr) || \
	__CMSG_LEN(cmsg) + sizeof(struct cmsghdr) >= __MHDR_END(mhdr) - (unsigned char *)(cmsg) \
	? 0 : (struct cmsghdr *)__CMSG_NEXT(cmsg))
#define CMSG_FIRSTHDR(mhdr) ((size_t) (mhdr)->msg_controllen >= sizeof (struct cmsghdr) ? (struct cmsghdr *) (mhdr)->msg_control : (struct cmsghdr *) 0)

#define CMSG_ALIGN(len) (((len) + sizeof (size_t) - 1) & (size_t) ~(sizeof (size_t) - 1))
#define CMSG_SPACE(len) (CMSG_ALIGN (len) + CMSG_ALIGN (sizeof (struct cmsghdr)))
#define CMSG_LEN(len)   (CMSG_ALIGN (sizeof (struct cmsghdr)) + (len))
// end copy-paste


struct cmsghdr *CNIOWASI_CMSG_FIRSTHDR(const struct msghdr *mhdr) {
    assert(mhdr != NULL);
    return CMSG_FIRSTHDR(mhdr);
}

struct cmsghdr *CNIOWASI_CMSG_NXTHDR(struct msghdr *mhdr, struct cmsghdr *cmsg) {
    assert(mhdr != NULL);
    assert(cmsg != NULL);
    return CMSG_NXTHDR(mhdr, cmsg);
}

const void *CNIOWASI_CMSG_DATA(const struct cmsghdr *cmsg) {
    assert(cmsg != NULL);
    return CMSG_DATA(cmsg);
}

void *CNIOWASI_CMSG_DATA_MUTABLE(struct cmsghdr *cmsg) {
    assert(cmsg != NULL);
    return CMSG_DATA(cmsg);
}

size_t CNIOWASI_CMSG_LEN(size_t payloadSizeBytes) {
    return CMSG_LEN(payloadSizeBytes);
}

size_t CNIOWASI_CMSG_SPACE(size_t payloadSizeBytes) {
    return CMSG_SPACE(payloadSizeBytes);
}

#endif // __wasi__