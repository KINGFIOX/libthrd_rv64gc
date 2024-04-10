// 用来测试线程栈
#include "thrd.h"

// 首先定义一个函数用于递归计算,递归则会占用栈空间
int fib(int n)
{
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

void matrix_sum(int* matrix, int col, int row, int* sum)
{
    // 创建暂存列和 的数组
    int* sums = (int*)malloc(sizeof(int) * col);
    memset(sums, 0, sizeof(int) * col);

    //  创建col-1个线程, 那么总共 就有 col 个线程
    int tid = thrd_create(col - 1);
    // 求和
    for (int j = 0; j < row; j++) {
        sums[tid] += matrix[tid * row + j];
    }
    // 等待所有线程执行完毕
    thrd_join();

    // 累加所有线程的求和结果
    for (int i = 0; i < col; i++) {
        *sum += sums[i];
    }
    free(sums);
}

int main(void)
{
	
	/* ---------- ---------- fib 并行计算 ---------- ---------- */

    // 并行,每个线程计算一个fib
    int count[4] = { 10, 12, 13, 14 };
    int expects[4] = { fib(count[0]), fib(count[1]), fib(count[2]), fib(count[3]) };
    int _results[4];
    int* results = _results;

    int id = thrd_create(3);

    // 并行区域
    results[id] = fib(count[id]);

    // 等待所有线程执行完毕
    thrd_join();

    // 检查结果
    for (int i = 0; i < 4; i++) {
        printf("results[%d]=%d\n", i, results[i]);
        printf("expects[%d]=%d\n", i, expects[i]);
        if (results[i] != expects[i]) {
            printf("Error: results[%d] != expects[%d]\n", i, i);
            // exit(-1);
        }
    }

	/* ---------- ---------- 矩阵并行计算 ---------- ---------- */

	// 定义个3行4列的矩阵
    int matrix[3][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    };
    // 定义一个求和结果
    int sum = 0;
    // 并行求和
    matrix_sum((int*)matrix, 3, 4, &sum);
    // 打印结果
    printf("sum=%d\n", sum);
    // assert(sum == 78);
    return 0;
}
