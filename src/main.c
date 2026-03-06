/* main.c */
/* Автор: Юранов Никита, группа 12 */

/*
 * КЛИЕНТ: ГЛАВНАЯ ПРОГРАММА
 * 
 */

#include "../include/airplane.h"
#include <stdlib.h>

int main(void)
{
    AIRPLANE2 flights[MAX_FLIGHTS];
    int flight_count = 0;
    int choice;
    char buffer[10];
    
    printf("========================================\n");
    printf("   ЛАБОРАТОРНАЯ РАБОТА 2, ЗАДАНИЕ 3\n");
    printf("   Тема: Структуры данных (AIRPLANE2)\n");
    printf("   Вариант 23\n");
    printf("   Автор: Юранов Никита, группа 12\n");
    printf("========================================\n");
    printf("\n ДОСТУПНЫЕ ФУНКЦИИ:\n");
    printf("   1. Ввод данных о рейсах (не менее 12)\n");
    printf("   2. Поиск рейса с максимальной скоростью\n");
    printf("   3. Поиск рейсов по марке самолета\n");
    printf("   4. Поиск рейса с минимальным расстоянием\n");
    printf("   5. Статистика по направлениям\n");
    printf("   6. Выход\n");
    
    while (1)
    {
        printf("\n--- МЕНЮ ---\n");
        printf("1. Ввод данных о рейсах\n");
        printf("2. Рейс с максимальной скоростью\n");
        printf("3. Рейсы по марке самолета\n");
        printf("4. Рейс с минимальным расстоянием\n");
        printf("5. Статистика по направлениям\n");
        printf("6. Выход\n");
        printf("Выберите действие (1-6): ");
        
        fgets(buffer, sizeof(buffer), stdin);
        choice = atoi(buffer);
        
        switch (choice)
        {
            case 1:
                create_flights(flights, &flight_count);
                break;
                
            case 2:
                print_max_speed_flight(flights, flight_count);
                break;
                
            case 3:
                print_flights_by_model(flights, flight_count);
                break;
                
            case 4:
                print_min_distance_flight(flights, flight_count);
                break;
                
            case 5:
                count_flights_by_destination(flights, flight_count);
                break;
                
            case 6:
                printf(" Программа завершена.\n");
                return 0;
                
            default:
                printf("❌ Неверный выбор. Пожалуйста, введите 1-6.\n");
        }
    }
    
    return 0;
}
