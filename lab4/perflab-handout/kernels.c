/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "my team",              /* Team name */

    "Jinbao Chen",     /* First member full name */
    "zkd18cjb@mail.ustc.edu.cn",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

char my_rotate_descr[] = "my_rotate: my implementation";
#define MOV(d, s) (*(d) = *(s))

pixel *mysrc;
pixel *mydst;
int my_dim;

void rotate_row(int *prow) {
    int dim = my_dim;
    int row = *prow;
    pixel *pdst = mydst + RIDX(row, 0, dim);
    pixel *psrc = mysrc + RIDX(0, dim-row-1, dim);
    for (int i = 0; i < dim; i+= 32) {
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
        MOV(pdst++, psrc);psrc += dim;
    }
}

void wait_all_threads(pthread_t* threads) {
    for (int i = 0; i < 32; i ++) {
        pthread_join(threads[i], NULL);
    }
}

void my_rotate_thread(int dim, pixel *src, pixel *dst) 
{
    my_dim = dim;
    mysrc = src;
    mydst = dst;
   
    pthread_t threads[32];
    int num_theads = 0;
    int rows[32];

    for (int i = 0; i < dim; i ++) {
        rotate_row(&i);
        if (num_theads >= 32) {
            wait_all_threads(threads);
            num_theads = 0;
        }
        rows[num_theads] = i;
        pthread_t my_thread;
        pthread_create(&my_thread, NULL, rotate_row, &rows[num_theads]);
        threads[num_theads++] = my_thread;
    }
	
	wait_all_threads(threads);    
}

void my_rotate(int dim, pixel *src, pixel *dst) {
    int i, j;
    for(i = 0; i < dim; i += 32){
        for(j = dim - 1; j >= 0; j --) {
            pixel* pdst = dst + RIDX(dim-1-j, i, dim);
            pixel* psrc = src + RIDX(i, j, dim);
            MOV(pdst, psrc);psrc += dim;
            MOV(pdst+1, psrc);psrc += dim;
            MOV(pdst+2, psrc);psrc += dim;
            MOV(pdst+3, psrc);psrc += dim;
            MOV(pdst+4, psrc);psrc += dim;
            MOV(pdst+5, psrc);psrc += dim;
            MOV(pdst+6, psrc);psrc += dim;
            MOV(pdst+7, psrc);psrc += dim;
            MOV(pdst+8, psrc);psrc += dim;
            MOV(pdst+9, psrc);psrc += dim;
            MOV(pdst+10, psrc);psrc += dim;
            MOV(pdst+11, psrc);psrc += dim;
            MOV(pdst+12, psrc);psrc += dim;
            MOV(pdst+13, psrc);psrc += dim;
            MOV(pdst+14, psrc);psrc += dim;
            MOV(pdst+15, psrc);psrc += dim;
            MOV(pdst+16, psrc);psrc += dim;
            MOV(pdst+17, psrc);psrc += dim;
            MOV(pdst+18, psrc);psrc += dim;
            MOV(pdst+19, psrc);psrc += dim;
            MOV(pdst+20, psrc);psrc += dim;
            MOV(pdst+21, psrc);psrc += dim;
            MOV(pdst+22, psrc);psrc += dim;
            MOV(pdst+23, psrc);psrc += dim;
            MOV(pdst+24, psrc);psrc += dim;
            MOV(pdst+25, psrc);psrc += dim;
            MOV(pdst+26, psrc);psrc += dim;
            MOV(pdst+27, psrc);psrc += dim;
            MOV(pdst+28, psrc);psrc += dim;
            MOV(pdst+29, psrc);psrc += dim;
            MOV(pdst+30, psrc);psrc += dim;
            MOV(pdst+31, psrc);psrc += dim;
        }
    }
}

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    naive_rotate(dim, src, dst);
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    // add_rotate_function(&rotate, rotate_descr);   
    add_rotate_function(&my_rotate, my_rotate_descr);  
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */

static int rsum[4096][4096];
static int gsum[4096][4096];
static int bsum[4096][4096];
char smooth_descr[] = "smooth: my smooth implementation";
void smooth(int dim, pixel *src, pixel *dst) 
{
    int dim1 = dim - 1;
    int dim2 = dim - 2;
	for(int i = 0; i < dim; i++){
		for(int j = 0; j < dim-2; j++){
            rsum[i][j] = 0, gsum[i][j] = 0, bsum[i][j] = 0;
			for(int k = j; k < j + 3; k++){
				rsum[i][j] += src[RIDX(i, k, dim)].red;
				gsum[i][j] += src[RIDX(i, k, dim)].green;
				bsum[i][j] += src[RIDX(i, k, dim)].blue;
			}
		}
	}
	// 中间部分
	for(int i = 1; i < dim-1; i++){
		for(int j = 1; j < dim-1; j++){
			dst[RIDX(i, j, dim)].red = (rsum[i-1][j-1]+rsum[i][j-1]+rsum[i+1][j-1]) / 9;
			dst[RIDX(i, j, dim)].green = (gsum[i-1][j-1]+gsum[i][j-1]+gsum[i+1][j-1]) / 9;
			dst[RIDX(i, j, dim)].blue = (bsum[i-1][j-1]+bsum[i][j-1]+bsum[i+1][j-1]) / 9;
		}
	}
    {   
        // 左上
        pixel *p1 = src + dim;
        dst[0].red = (src[0].red + src[1].red + p1[0].red + p1[1].red) >> 2;
        dst[0].green = (src[0].green + src[1].green + p1[0].green + p1[1].green) >> 2;
        dst[0].blue = (src[0].blue + src[1].blue + p1[0].blue + p1[1].blue) >> 2;
    }
    {
        //右上
        pixel *psrc = src + dim2;
        pixel *p1 = src + RIDX(1, dim2, dim);
        pixel *pdst = dst + dim1;
        pdst[0].red = (psrc[0].red + psrc[1].red + p1[0].red + p1[1].red) >> 2;
        pdst[0].green = (psrc[0].green + psrc[1].green + p1[0].green + p1[1].green) >> 2;
        pdst[0].blue = (psrc[0].blue + psrc[1].blue + p1[0].blue + p1[1].blue) >> 2;
    }
    {
        //左下
        pixel *psrc = src + RIDX(dim2, 0, dim);
        pixel *p1 = src + RIDX(dim-1, 0, dim);
        pixel *pdst = dst + RIDX(dim-1, 0, dim);
        pdst[0].red = (psrc[0].red + psrc[1].red + p1[0].red + p1[1].red) >> 2;
        pdst[0].green = (psrc[0].green + psrc[1].green + p1[0].green + p1[1].green) >> 2;
        pdst[0].blue = (psrc[0].blue + psrc[1].blue + p1[0].blue + p1[1].blue) >> 2;
    }
    {
        //右下
        pixel *psrc = src + RIDX(dim2, dim2, dim);
        pixel *p1 = src + RIDX(dim-1, dim2, dim);
        pixel *pdst = dst + RIDX(dim-1, dim-1, dim);
        pdst[0].red = (psrc[0].red + psrc[1].red + p1[0].red + p1[1].red) >> 2;
        pdst[0].green = (psrc[0].green + psrc[1].green + p1[0].green + p1[1].green) >> 2;
        pdst[0].blue = (psrc[0].blue + psrc[1].blue + p1[0].blue + p1[1].blue) >> 2;
    }
    //row 1
    for (int j = 1; j < dim1; j++) {
        dst[j].red = (rsum[0][j-1] + rsum[1][j-1]) / 6;
        dst[j].green = (gsum[0][j-1] + gsum[1][j-1]) / 6;
		dst[j].blue = (bsum[0][j-1] + bsum[1][j-1]) / 6;
    }
    // col 1
    for(int i = 1; i < dim1; i++){
		int index1 = RIDX(i-1, 0, dim), index2 = RIDX(i-1, 1, dim);
        int dindex = RIDX(i, 0, dim), index4 = RIDX(i, 1, dim);
        int index5 = RIDX(i+1, 0, dim), index6 = RIDX(i+1, 1, dim);
		dst[dindex].red = (src[index1].red + src[index2].red + src[dindex].red + src[index4].red + src[index5].red + src[index6].red) / 6;
		dst[dindex].green = (src[index1].green + src[index2].green + src[dindex].green + src[index4].green + src[index5].green + src[index6].green) / 6;
		dst[dindex].blue = (src[index1].blue + src[index2].blue + src[dindex].blue + src[index4].blue + src[index5].blue + src[index6].blue) / 6;
	}
    // last col
	for(int i = 1; i < dim1; i++){
        int index1 = RIDX(i-1, dim2, dim), index2 = RIDX(i-1, dim1, dim);
        int index3 = RIDX(i, dim2, dim), dindex = RIDX(i, dim1, dim);
        int index5 = RIDX(i+1, dim2, dim), index6 = RIDX(i+1, dim1, dim);
		dst[dindex].red = (src[index1].red + src[index2].red + src[index3].red + src[dindex].red + src[index5].red + src[index6].red) / 6;
		dst[dindex].green = (src[index1].green + src[index2].green + src[index3].green + src[dindex].green + src[index5].green + src[index6].green) / 6;
		dst[dindex].blue = (src[index1].blue + src[index2].blue + src[index3].blue + src[dindex].blue + src[index5].blue + src[index6].blue) / 6;
	}
    // last row
    pixel *p2 = dst + RIDX(dim1, 0, dim);
	for(int j = 1; j < dim1; j++){
		p2[j].red = (rsum[dim1][j-1]+rsum[dim2][j-1]) / 6;
		p2[j].green = (gsum[dim1][j-1]+gsum[dim2][j-1]) / 6;
		p2[j].blue = (bsum[dim1][j-1]+bsum[dim2][j-1]) / 6;
	}
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

