#pragma once

// 创建一个线程并且返回线程的编号(主线程返回0,其他线程返回非0正值),线程中的函数自当前之后下一行开始执行,如果创建线程失败返回-1
int thrd_create();
// 等待之前所有创建的子线程结束,在这之后只有主线程继续执行,失败返回-1
int thrd_join();
// 创建一个互斥锁并且返回锁的编号(大于0的值),如果创建失败,返回-1
int mtx_create();
// 对指定编号的互斥锁在 共享区 上锁
void mtx_lock(int mtx);
// 对指定编号的互斥锁在 共享区 解锁
void mtx_unlock(int mtx);
