#include "Stdafx.h"
using namespace std;

void HardLevelTask()
{
	/*
В первом файле хранится k матриц из n строк и n+1 столбцов каждая (последний столбец - столбец свободных членов).
Во втором файле хранится k векторов - результатов решений соответствующих систем ЛАУ с матрицами из первого файла.
Вывести на экран покомпонентно исходную систему уравнений и результат, проверив его предварительно; добавить в 
файлы новые данные; удалить ненужную информацию
	*/
	cout << "\Hard level task:\n";

    ///<Код для считывания матрицы с файла(недопиленный)>
   /* std::ifstream fstream("test.txt");
    while (fstream.peek() != EOF)
    {
        std::string line;
        while (std::getline(fstream, line) && !line.empty())
        {
            double x;
            for (std::stringstream stream(line); stream >> x;)
                std::cout << x << " ";
            std::cout << std::endl;
        }
        std::cout << "конец матрицы" << std::endl;
    }*/
    ///<\Код для считывания матрицы с файла(недопиленный)>
    unsigned k, n, m = 1;
    char FileName[20] =      "matrix",
        FileNameSecond[20] = "vectors",
        FileNameThird[20] =  "workfile";
    while (true)
    {
        printf("\nEnter k number of matrixs in first and number vectors in second files $ ");
        scanf("%d", &k);

        printf("\nEnter n  dimentions of matrixs(nxn+1): ");
        scanf("%d", &n);
        if ((k > 0) && (n > 0)  )
            break;
        printf("\nNumber is incorrect!!! Try ” “again!!!\n");
    }
   /*
    printf("\nEnter the name of first file: ");
    scanf("%s", FileName);
    BlockWriteFile(FileName, "wb", k, n, n + 1);

    printf("\nEnter the name of second file: ");
    scanf("%s", FileNameSecond);
    BlockWriteFile(FileNameSecond, "wb", k, 1, n);


    printf("\nEnter the name of third file: ");
    scanf("%s", FileNameThird);
    */
    system("cls");
    BlockWriteFile(FileName, "wb", k, n, n + 1);
    BlockWriteFile(FileNameSecond, "wb", k, 1, n);

    printf("\nThe contents of files:\n");
    printf("Файл <<%s>> состоящий из %d матриц размерности %dx%d последний столбец столбуц свободных членов коэфициентов при неизвесных\nдля СЛАУ:\n",FileName, k,n,n+1);
    DisplayFile(FileName, "rb", n, n+1);

    printf("Файл <<%s>> состоящий из %d  результатов решений соответствующих"
        "\nСЛАУ с матрицами из первого файла",FileNameSecond,k);
    DisplayFile(FileNameSecond, "rb", m, n);

    cout << "\n===========================================================================\n";
    cout << "Вывод полученных СЛАУ: \n";
    WorkFile(FileName, FileNameSecond, k, n,( n + 1));

 /*   printf("\nФайл <<%s>> состоящий из %d  результатов решений\nсоответствующих"
        " СЛАУ с матрицами из первого файла", FileNameSecond, k);
    DisplayFile(FileNameSecond, "rb", m, n);*/
    
}
double** InizializateMat(int row, int col)
{
    double** Matrix = new double* [col];
    for (size_t i = 0; i < row; i++)
    {
        Matrix[i] = new double[col] ;
    }
    return Matrix;
}
void WorkFile(char* FileName, char* FileNameSecond, int Count_MatsOrVectors, int row, int col)
{
    double* matrix;
       double * Y, 
              * X;
       int bufsize = row * col;// *sizeof(int);
    matrix = FreeMemory(row, col);
  //  matrix = InizializateMat(matrix, row, col);

    Y = new double[row];
    FILE* f_in, * f_out;

    f_in = fopen(FileName, "rb");
    long i = 1;

    int newbufsize = row * (col-1);
   double** MatForSLAY ;
   MatForSLAY = InizializateMat(row, (col-1));
   int indexrowMat = 0,
       indexcolMat = 0,
       indexmat = 0,
       indexY = 0;
   double BufferSize = row * col * sizeof(double);
   double** mas = new double* [row];
   for (size_t i = 0; i < row; i++)
   {
       mas[i] = new double[col] ;
   }

   f_out = fopen(FileNameSecond, "wb");
    while(fread(matrix, BufferSize, 1, f_in) != 0)
    {
        printf("\n%d-ая СЛАУ: \n ", i ); 
        indexmat = 0;
        for (size_t i = 0; i < row; i++)
        {
            for (size_t q = 0; q < col; q++)
            {
                mas[i][q] = matrix[indexmat];
                indexmat++;
            }
        }
        indexY = 0;
        for (size_t i = 0; i < row; i++)
        {
            for (size_t q = 0; q < col; q++)
            {
                if (q == col - 1)
                {
                    Y[indexY] = mas[i][q];
                    indexY++;
                }
                if (q != col - 1)
                {
                    MatForSLAY[i][q] = mas[i][q];
                }
            }
        }
        sysout(MatForSLAY, Y, row);
        X = gauss(MatForSLAY, Y, row);
     /*   rewind(f_out);
        if (i % 2 == 0)
        {
           fseek(f_out, 8L, SEEK_SET);
            fwrite(X, sizeof(double)*row, 1, f_out);
       }*/
        if (X != 0)
        {
            cout << "\nРешение " << i << "-ой СЛАУ: \n";
            for (int i = 0; i < row; i++)
            {
                cout << "\tX[" << i << "] = ";
                printf("%1.1f", X[i]);
            }
        }
        i++;
    }
    fclose(f_in);
    fclose(f_out);
}

double* InitMatrix(unsigned l, unsigned n, unsigned m)
{
    unsigned i;
    double* Pointer = (double*)malloc((n * m) * sizeof(double));
    for (i = 0; i < n * m; i++) { Pointer[i] = 1.0+(rand()%20)/10.0; }
    return Pointer;
}

double* FreeMemory(unsigned n, unsigned m)
{
    double* Pointer = (double*)malloc((n * m) * sizeof(double));
    return Pointer;
}

int BlockWriteFile(char* FileName, const char* Mode, unsigned count_matrix, unsigned row, unsigned col)
{
    int BufSize = sizeof(double) * row * col,
        counter_matrix = 0;
    double* Pointer = (double*)malloc(BufSize);
    unsigned i;
    FILE* FilePointer = fopen(FileName, Mode);
    if (FilePointer == NULL)
    {
        printf("Can't open file to write.");
        getchar();
        abort();
    }

    for (i = 0; i < count_matrix; i++)
    {
        Pointer = InitMatrix(i, row, col);
        counter_matrix++;
        fwrite(Pointer, BufSize, 1, FilePointer);

    }
    fclose(FilePointer);
    free(Pointer);
    return counter_matrix;
}
void DisplayFile(const char* String, const char* Mode, unsigned n, unsigned m)
{
    int BufSize = sizeof(double) * n * m, Sector = 0;
    double* Pointer = FreeMemory(n, m);
    FILE* FilePointer = fopen(String, Mode);
    if (FilePointer == NULL) { printf("\nCan't open file to read."); getchar(); abort(); }

    while (fread(Pointer, BufSize, 1, FilePointer) != 0)
    {
       (n==1) ? printf("\n %d's  vector \n", (Sector + 1))
              :
                printf("\n %d's  matrix \n", (Sector + 1));
        DisplayMatrix(Pointer, n, m);
        Sector++;
    }
    fclose(FilePointer);
    free(Pointer);
}

void DisplayMatrix(double* Pointer, unsigned n, unsigned m)
{
    unsigned i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%1.1f ", *(Pointer + i * m + j));
        }
        printf("\n");
    }
}

// Вывод системы уравнений
void sysout(double** a, double* y, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%1.1f *x%d",a[i][j],j);
         //   cout << a[i][j] << "*x" << j;
            if (j < n - 1)
                cout << " + ";
        }
        printf(" = %1.1f\n",y[i]);
       // cout << " = " << y[i] << endl;
    }
    return;
}
void swap(double& a, double& b)
{
    double temp = a;
    a = b;
    b = temp;
}

double* gauss(double** a, double* y, int n)
{
    double* x, max=0;
    int k=0, index=0;
    const double eps = 0.000001;  // точность
    x = new double[n];
    k = 0;
    while (k < n)
    {
        // Поиск строки с максимальным a[i][k]
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        // Перестановка строк
        if (max < eps)
        {
            // нет ненулевых диагональных элементов
            cout << "Решение получить невозможно из-за нулевого столбца ";
            cout << index << " матрицы A" << endl;
            return 0;
        }
        for (int j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        // Нормализация уравнений
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)  continue; // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }
    // обратная подстановка
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return x;
}

void DeleteUnwantedMatrixOfFile(char* String, unsigned count_wr_mat, unsigned n, unsigned m)
{
    int* Pointer = (int*)malloc(sizeof(int) * m * n * count_wr_mat);
    int  BufSize = sizeof(int) * n * m * count_wr_mat;
    long lastmatrixforw = (long)(sizeof(int) * n * m * count_wr_mat);
    int* Simple = nullptr,
        Sum = 0;

    FILE* FilePointer = fopen(String, "rb");
    FILE* TempFile = fopen("TempFile", "wb");
    if (FilePointer == NULL)
    {
        printf("Can't open file to read.");
        getchar();
        abort();
    }

    long set_possition = 0;
    int count_rd_mat = 1;

    fread(Pointer, BufSize, 1, FilePointer);

    fwrite(Pointer, BufSize, 1, TempFile);

    rewind(FilePointer);

    fclose(FilePointer);
    fclose(TempFile);

    FilePointer = fopen(String, "w+b");

    TempFile = fopen("TempFile", "rb");

    fread(Pointer, BufSize, 1, TempFile);

    fwrite(Pointer, BufSize, 1, FilePointer);

    fclose(FilePointer);
    fclose(TempFile);

    free(Pointer);
    free(Simple);
}

void FillNewFileUnwantedMatrix(char* FileName1, char* FileName2, unsigned set_pos, unsigned count_matrix, unsigned row, unsigned col)
{
    int BufSize = sizeof(int) * row * col,
        counter_matrix = 0;
    int* Pointer = (int*)malloc(BufSize);
    unsigned i;
    FILE* FilePointer1 = fopen(FileName1, "rb");
    FILE* FilePointer2 = fopen(FileName2, "wb");

    if (FilePointer1 == NULL)
    {
        printf("Can't open file to write.");
        getchar();
        abort();
    }


    long set_possition = sizeof(int) * row * col * set_pos;

    for (i = 0; i < count_matrix; i++)
    {
        fseek(FilePointer1, set_possition, SEEK_SET);

        fread(Pointer, BufSize, 1, FilePointer1);
        counter_matrix++;
        fwrite(Pointer, BufSize, 1, FilePointer2);
        set_possition += static_cast<long>(sizeof(int) * row * col);
    }
    fclose(FilePointer1);
    fclose(FilePointer2);

    free(Pointer);
}



