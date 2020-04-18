#include <iostream>

using namespace std;

int** new_matrix(size_t n)
{
    int **arr = new int*[n];
    size_t i;
    for (i=0; i < n; i++)
    {
        arr[i] = new int[n];
    }
    return arr;
}

void free_matrix(int **arr, size_t n)
{
    size_t i;
    for (i=0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

long long determinate(int **arr, size_t n)
{
    cout<<"iteration "<<n<<endl;
    if (n == 3) {
        return
            arr[0][0] * arr[1][1] * arr[2][2] +
            arr[0][1] * arr[1][2] * arr[2][0] +
            arr[0][2] * arr[1][0] * arr[2][1] -
            arr[0][2] * arr[1][1] * arr[2][0] -
            arr[0][0] * arr[1][2] * arr[2][1] -
            arr[0][1] * arr[1][0] * arr[2][2];
    }
    n--;

    int **minor = new_matrix(n);
    size_t m, i, j, ii;
    bool sign = false;
    long long r = 0;
    for (m = 0; m <= n; m++)
    {
        for (i = 1; i <= n; i++)
        {
            ii = i - 1;
            for (j = 0; j < m; j++)
            {
                minor[ii][j] = arr[i][j];
            }
            for (j++; j <= n; j++)
            {
                minor[ii][j-1] = arr[i][j];
            }
        }

        if (sign) {
            r = r - arr[0][m] * determinate(minor, n);
        } else {
            r = r + arr[0][m] * determinate(minor, n);
        }
        sign = !sign;
    }
    free_matrix(minor, n);
    return r;
}

int main()
{
    size_t n,i,j;
    cin>>n;

    int **arr = new_matrix(n);
    for (i=0; i < n; i++)
    {
        for (j=0; j < n; j++)
        {
            cin>>arr[i][j];
        }
    }

    long long r;

    if (n==1) {
        r = arr[0][0];
    }
    else if (n==2) {
        r = arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
    }
    else {
        r = determinate(arr,n);
    }
    cout<<"Result: "<<r<<endl;

    free_matrix(arr, n);
    return 0;
}
