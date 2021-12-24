

#include <iostream>
#include <iomanip>


int ElemetsValid();

int** CreateMatr(int sizeRow_, int sizeCol_);
void InputMatr(int** matr, int sizeRow_, int sizeCol_);
void PrintMatr(int** matr, int sizeRow_, int sizeCol_);
void DeleteMatr(int** matr, int sizeRow_);
int SummMatr(int** matr, int sizeRow_, int sizeCol_);

int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "Введите количество строк матрицы: ";
    int sizeRow = ElemetsValid();
    std::cout << "Введите количество столбцов матрицы: ";
    int sizeCol = ElemetsValid();

    int** matr = CreateMatr(sizeRow, sizeCol);
    InputMatr(matr, sizeRow, sizeCol);
    std::cout << " Матрица:\n";
    PrintMatr(matr, sizeRow, sizeCol);

    std::cout << "Минимум всех сумм абсолютных элементов: " << SummMatr(matr, sizeRow, sizeCol);
    DeleteMatr(matr, sizeRow);

    return 0;
}



int ElemetsValid() // проверка корректности введенных значений
{
    bool isCorrectInput = false;
    int element;
    do
    {
        std::cin >> element;
        // переменная elemnt имеет тип int, значит будет проведено соответсвие с типом int. Если будет введено значение типа double, то соответствия между типами не будет и выведется ошибка
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(255, '\n');
            std::cout << "Ошибка ввода! Введите еще раз!" << std::endl;
        }
        else
            isCorrectInput = true;
    } while (!isCorrectInput);

    return element;
}

// создание динамического двумерного массива
int** CreateMatr(int sizeRow_, int sizeCol_)
{
    int** matr = new int* [sizeRow_];
    for (int i = 0; i < sizeRow_; i++)
    {
        matr[i] = new int[sizeCol_];
    }
    return matr;
}

// Заполнение динамического двумерного массива рандоммными элементами
void InputMatr(int** matr, int sizeRow_, int sizeCol_)
{
    for (int i = 0; i < sizeRow_; i++)
        for (int j = 0; j < sizeCol_; j++)
            matr[i][j] = rand() % -10;
}

// Вывод массива
void PrintMatr(int** matr, int sizeRow_, int sizeCol_)
{
    for (int i = 0; i < sizeRow_; i++)
    {
        for (int j = 0; j < sizeCol_; j++)
            // setw используется для установки количества символов, которые будут использоваться в качестве ширины поля для следующей операции вставки
            std::cout << std::setw(3) << matr[i][j] << " ";
        std::cout << "\n";
    }
}

// Освобождение выделенной под динмический двумерный массив памяти
void DeleteMatr(int** matr, int sizeRow_)
{
    for (int i = 0; i < sizeRow_; i++)
        delete[] matr[i];
    delete[] matr;
}


int SummMatr(int** matr, int sizeRow_, int sizeCol_)
{
    int sum = 0, min = 0;
    // вычисляем сумму 1го столбца для того чтобы потом его сравнивать с остальными и искать минимум
    for (int i = 0; i < sizeRow_; i++)
        min += matr[i][0];
    // начинаем со 2го столбца
    for (int i = 1; i < sizeCol_; i++)
    {
        for (int j = 0; j < sizeRow_; j++)
        {
            // добавляем в сумму 
            sum += abs(matr[j][i]);
        }
        // сравниваем
        if (sum < min)
            min = sum;
        // обнуляем сумму, для подсчета дальнейших столбцов
        sum = 0;
    }
    return min;
}

