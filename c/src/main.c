#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char q=1; //size of margin
const char lw=10+2*q, lk=10+2*q, lm=10;

void define_colour()
{
    #define RESET   "\033[0m"
    #define BLACK   "\033[30m"
    #define RED     "\033[31m"
    #define GREEN   "\033[32m"
    #define YELLOW  "\033[33m"
    #define BLUE    "\033[34m"
    #define MAGENTA "\033[35m"
    #define CYAN    "\033[36m"
    #define WHITE   "\033[37m"
}

void create_void(short int t[lw][lk], bool h[lw][lk])
{
    for (int w=0; w<lw; w++)
    {
        for (int k=0; k<lk; k++)
        {
            t[w][k]=10;
        }
    }
    for (int w=q; w<lw-q; w++)
    {
        for (int k=q; k<lk-q; k++)
        {
            t[w][k]=0;
        }
    }
    for (int w=0; w<lw; w++)
    {
        for (int k=0; k<lk; k++)
        {
            h[w][k]=false;
        }
    }
}

void create_mines(short int t[lw][lk], bool h[lw][lk], int w0, int k0)
{
    int m, n=0, o;
    srand(time(NULL));
    while(n!=lm)
    {
        m=rand()%(lw-2*q)+q, o=rand()%(lk-2*q)+q;
        if(t[m][o]==0)
        {
            if(!((m==w0-1||m==w0||m==w0+1)&&(o==k0-1||o==k0||o==k0+1)))
            {
                t[m][o]=9;
                n++;
            }
        }
    }
    for (int w=q; w<lw-q; w++)
    {
        for (int k=q; k<lk-q; k++)
        {
            if(t[w][k]==0)
            {
                if(t[w-1][k-1]==9)
                t[w][k]+=1;
                if(t[w-1][k]==9)
                t[w][k]+=1;
                if(t[w-1][k+1]==9)
                t[w][k]+=1;
                if(t[w][k-1]==9)
                t[w][k]+=1;
                if(t[w][k+1]==9)
                t[w][k]+=1;
                if(t[w+1][k-1]==9)
                t[w][k]+=1;
                if(t[w+1][k]==9)
                t[w][k]+=1;
                if(t[w+1][k+1]==9)
                t[w][k]+=1;
            }
        }
    }
}

void output(short int t[lw][lk], bool h[lw][lk])
{
    printf(" ");
    for (int k=q; k<lk-q; k++)
        printf(" %i", k-q+1);
    printf("\n");
    for (int w=q; w<lw-q; w++)
    {
        printf("%i", w-q+1);
        for (int k=q; k<lk-q; k++)
        {
            printf(" ");
            if(h[w][k])
            {
                if(t[w][k]==0)
                    printf(BLUE);
                if(t[w][k]==1)
                    printf(CYAN);
                if(t[w][k]==2)
                    printf(GREEN);
                if(t[w][k]==3)
                    printf(YELLOW);
                if(t[w][k]>=3)
                    printf(RED);
                printf("%hi", t[w][k]);
            }
            else
            {
                printf(RESET);
                printf("H");
            }
        }
        printf("\n");
    }
}

void spread0(short int t[lw][lk], bool h[lw][lk], int w, int k)
{
    h[w-1][k-1]=true;
    h[w-1][k]=true;
    h[w-1][k+1]=true;
    h[w][k-1]=true;
    h[w][k+1]=true;
    h[w+1][k-1]=true;
    h[w+1][k]=true;
    h[w+1][k+1]=true;
}

void spread(short int t[lw][lk], bool h[lw][lk], int w, int k)
{
    if(t[w-1][k-1]==0&&h[w-1][k-1])
    {
        spread0(t, h, w-1, k-1);
        //spread(t, h, w-1, k-1);
    }
    if(t[w-1][k]==0&&h[w-1][k])
    {
        spread0(t, h, w-1, k);
        //spread(t, h, w-1, k);
    }
    if(t[w-1][k+1]==0&&h[w-1][k+1])
    {
        spread0(t, h, w-1, k+1);
        //spread(t, h, w-1, k+1);
    }
    if(t[w][k-1]==0&&h[w][k])
    {
        spread0(t, h, w, k-1);
        //spread(t, h, w, k-1);
    }
    if(t[w][k+1]==0&&h[w][k])
    {
        spread0(t, h, w, k+1);
        //spread(t, h, w, k+1);
    }
    if(t[w+1][k-1]==0&&h[w][k])
    {
        spread0(t, h, w+1, k-1);
        //spread(t, h, w+1, k-1);
    }
    if(t[w+1][k]==0&&h[w][k])
    {
        spread0(t, h, w+1, k);
        //spread(t, h, w+1, k);
    }
    if(t[w+1][k+1]==0&&h[w][k])
    {
        spread0(t, h, w+1, k+1);
        //spread(t, h, w+1, k+1);
    }
}

void input(short int t[lw][lk], bool h[lw][lk])
{
    int w, k;
    printf("\ntype in coordinates (w k)\n");
    scanf("%i", &w);
    scanf("%i", &k);
    h[w][k]=true;
    if(t[w][k]==0&&h[w][k])
    {
        spread0(t, h, w, k);
        spread(t, h, w, k);
    }
}

bool check(short int t[lw][lk], bool h[lw][lk])
{
    for (int w=q; w<lw-q; w++)
    {
        for (int k=q; k<lk-q; k++)
        {
            if(h[w][k]&&t[w][k]==9)
                return false;
        }
    }
    short int n=0;
    for (int w=q; w<lw-q; w++)
    {
        for (int k=q; k<lk-q; k++)
        {
            if(!h[w][k])
                n++;
        }
    }
    if(n==lm)
    return false;
    return true;
}

int main()
{
    define_colour();
    short int t[lw][lk];
    bool h[lw][lk];
    create_void(t,h);
    output(t,h);
        int w, k;
        printf("\ntype in coordinates (w k)\n");
        scanf("%i", &w);
        scanf("%i", &k);
        t[w][k]=0;
        h[w][k]=true;
        spread0(t, h, w, k);
        printf("\n");
    create_mines(t,h,w,k);
        output(t,h);
    while(check(t,h))
    {
        input(t,h);
        printf("\n");
        output(t,h);
    }
    return 0;
}