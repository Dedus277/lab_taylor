#include <stdio.h>
#include <math.h>

int main(void)
{
    int N; // число равных частей
    double a = 0.0; // левая граница отрезка 
    double b = 1.0; // правая граница отрезка 
    double epsilon = 1.0;
    double k = 10.0; // выбрано после сравнения результатов при k = 1 и k = 10

    // находим машинное epsilon: уменьшаем его до предела точности.
    while (1.0 + epsilon / 2.0 > 1.0)//находим epsilon 
    {
        epsilon /= 2.0;
    }

    printf("Enter the number of parts N:");
    if (scanf("%d", &N) != 1)
    {
        return 1;
    }
    if (N <= 0)
    {
        return 2;
    }

    double h = (b - a) / N; // длина одного шага между соседними точками
    printf("x\tTaylor\t\tLibrary\tAbsoluteError\n");

    // перебираем точки отрезка, включая обе границы.
    for (int i = 0; i <= N; i++)
    {
        double x = a + i * h; // Текущий аргумент функции.
        double library_value = sin(x) * sin(x);

        double term = x * x; // текущее слагаемое
        double sum = term; // сумма  слагаемых
        int j = 1; // номер первого слагаемого ряда

        // считаем следующие члены ряда, не превышая 100 слагаемых всего
        while (j < 100)
        {
            term = -term * (4.0 * x * x) / ((2.0 * j + 1)*(2.0 * j + 2.0));
            sum += term; // добавляем найденный член к сумме ряда
            j++;

            // останавливаемся, когда очередной член меньше epsilon * k
            if (fabs(term) <= epsilon * k)
            {
                break;
            }
        }

        double error = fabs(sum - library_value); // абсолютное расхождение двух способов
        printf("%.2f\t%.12f\t%.12f\t%.3e\n", x, sum, library_value, error);
    }

    return 0;
}
