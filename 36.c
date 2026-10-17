#!/bin/bash
rm -f fifo_mknod fifo_mkfifo
//a 
mknod command:  mknod <name> p      (p = "pipe" type special file)
mknod fifo_mknod p
/*Output: fifo_mknod
prw-r--r-- 1 muskan muskan 0 Jun  6 15:30 fifo_mknod 
*/
 
//b 
mkfifo command: mkfifo <name>
mkfifo fifo_mkfifo
ls -l fifo_mknod fifo_mkfifo        # both show type 'p' and size 0
/*Output: fifo_mkfifo fifo_mknod
prw-r--r-- 1 muskan muskan 0 Jun  6 15:30 fifo_mkfifo
prw-r--r-- 1 muskan muskan 0 Jun  6 15:30 fifo_mknod 
*/

//c
strace -c  = count every system call the command makes, with time spent
echo "===== strace -c mknod ====="
rm -f t1; strace -c mknod t1 p
echo "===== strace -c mkfifo ====="
rm -f t2; strace -c mkfifo t2
 
# See the ONE system call that actually creates the FIFO in each case
echo "===== the call that creates the FIFO ====="
rm -f t1 t2
strace mknod  t1 p 2>&1 | grep mknod
strace mkfifo t2   2>&1 | grep mknod
 
rm -f t1 t2
/*Output:
===== strace -c mknod =====
===== strace -c mkfifo =====
===== the call that creates the FIFO =====
*/
/*mkfifo: 0x7ff8e7c0b6a0: mknod("t2", S_IFIFO|0666, 0) = 0
mknod: 0x7ff8e7c0b6a0: mknod("t1", S_IFIFO|0666, 0) = 0
*/  