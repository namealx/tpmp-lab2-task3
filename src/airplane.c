/* airplane.c */
/* Автор: Юранов Никита, группа 12 */

/*
 * СЕРВЕР: РЕАЛИЗАЦИЯ ФУНКЦИЙ ДЛЯ РАБОТЫ С АВИАРЕЙСАМИ
 * 
 */

#include "../include/airplane.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * ПРИВАТНЫЕ ФУНКЦИИ (доступны только внутри этого файла)
 */

/*
 * Безопасный ввод строки с удалением символа новой строки
 */
static void safe_string_input(char buffer[], int size)
{
    fgets(buffer, size, stdin);
    /* Удаляем \n в конце строки */
    buffer[strcspn(buffer, "\n")] = '\0';
}

/*
 * Безопасный ввод целого числа
 */
static int safe_int_input(const char prompt[])
{
    int value;
    char buffer[20];
    
    printf("%s", prompt);
    safe_string_input(buffer, sizeof(buffer));
    value = atoi(buffer);
    
    return value;
}

/*
 * Ввод времени (часы и минуты)
 */
static Time input_time(const char prompt[])
{
    Time t;
    
    printf("%s\n", prompt);
    t.hours = safe_int_input("  Часы (0-23): ");
    t.minutes = safe_int_input("  Минуты (0-59): ");
    
    /* Валидация */
    if (t.hours < 0 || t.hours > 23)
    {
        printf("  Неверные часы. Установлено 0.\n");
        t.hours = 0;
    }
    if (t.minutes < 0 || t.minutes > 59)
    {
        printf("  Неверные минуты. Установлено 0.\n");
        t.minutes = 0;
    }
    
    return t;
}

/*
 * Функция для сравнения строк без учета регистра
 */
static int strcasecmp_custom(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (tolower(*s1) != tolower(*s2))
        {
            return tolower(*s1) - tolower(*s2);
        }
        s1++;
        s2++;
    }
    return tolower(*s1) - tolower(*s2);
}

/*
 * ПУБЛИЧНЫЕ ФУНКЦИИ
 */

/*
 * Функция 1: СОЗДАНИЕ МАССИВА ЗАПИСЕЙ (не менее 12)
 */
void create_flights(AIRPLANE2 flights[], int *count)
{
    int i;
    int num_flights;
    char buffer[MAX_STRING];
    
    printf("Введите количество рейсов (макс. %d): ", MAX_FLIGHTS);
    safe_string_input(buffer, sizeof(buffer));
    num_flights = atoi(buffer);
    
    /* Проверка на максимальное количество */
    if (num_flights > MAX_FLIGHTS)
    {
        printf("Количество рейсов ограничено %d\n", MAX_FLIGHTS);
        num_flights = MAX_FLIGHTS;
    }
    
    /* Проверка на минимальное количество (не менее 12) */
    if (num_flights < 12)
    {
        printf("ВНИМАНИЕ: По заданию требуется не менее 12 записей.\n");
        printf("Вы ввели только %d. Рекомендуется добавить еще.\n", num_flights);
    }
    
    /* Цикл ввода данных для каждого рейса */
    for (i = 0; i < num_flights; i++)
    {
        printf("\n--- Ввод данных для рейса %d ---\n", i + 1);
        
        /* Номер рейса */
        flights[i].flight_number = safe_int_input("Номер рейса: ");
        
        /* Время вылета и прилета */
        flights[i].departure_time = input_time("Время вылета:");
        flights[i].arrival_time = input_time("Время прилета:");
        
        /* Направление */
        printf("Направление (город): ");
        safe_string_input(flights[i].destination, MAX_STRING);
        
        /* Марка самолета */
        printf("Марка самолета: ");
        safe_string_input(flights[i].aircraft_model, MAX_STRING);
        
        /* Расстояние */
        flights[i].distance = safe_int_input("Расстояние (км): ");
        if (flights[i].distance <= 0)
        {
            printf("  Расстояние должно быть положительным. Установлено 100.\n");
            flights[i].distance = 100;
        }
    }
    
    *count = num_flights;
    printf("\n Добавлено %d рейсов\n", *count);
}

/*
 * ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ: ВЫЧИСЛЕНИЕ СКОРОСТИ
 */
double calculate_speed(AIRPLANE2 flight)
{
    int departure_seconds, arrival_seconds, flight_seconds;
    double flight_hours;
    
    /* Переводим время в секунды */
    departure_seconds = flight.departure_time.hours * 3600 + 
                        flight.departure_time.minutes * 60;
    arrival_seconds = flight.arrival_time.hours * 3600 + 
                      flight.arrival_time.minutes * 60;
    
    /* Если прилет на следующий день */
    if (arrival_seconds < departure_seconds)
    {
        arrival_seconds += 24 * 3600;
    }
    
    /* Длительность полета в секундах и часах */
    flight_seconds = arrival_seconds - departure_seconds;
    flight_hours = (double)flight_seconds / SECONDS_IN_HOUR;
    
    /* Вычисляем скорость */
    if (flight_hours > 0)
    {
        return flight.distance / flight_hours;
    }
    
    return 0.0;
}

/*
 * Функция 2: ПОИСК РЕЙСА С МАКСИМАЛЬНОЙ СКОРОСТЬЮ
 */
int find_max_speed_flight(AIRPLANE2 flights[], int count)
{
    int i;
    int max_index = 0;
    double max_speed = 0.0;
    double current_speed;
    
    if (count <= 0)
    {
        return -1;
    }
    
    for (i = 0; i < count; i++)
    {
        current_speed = calculate_speed(flights[i]);
        if (current_speed > max_speed)
        {
            max_speed = current_speed;
            max_index = i;
        }
    }
    
    return max_index;
}

/*
 * Функция 2 (вывод): ВЫВОД РЕЙСА С МАКСИМАЛЬНОЙ СКОРОСТЬЮ
 */
void print_max_speed_flight(AIRPLANE2 flights[], int count)
{
    int index;
    double speed;
    
    index = find_max_speed_flight(flights, count);
    
    if (index >= 0)
    {
        speed = calculate_speed(flights[index]);
        
        printf("\n  РЕЙС С МАКСИМАЛЬНОЙ СКОРОСТЬЮ \n");
        printf("========================================\n");
        printf("Скорость: %.1f км/ч\n", speed);
        printf("Номер рейса: %d\n", flights[index].flight_number);
        printf("Время вылета: %02d:%02d\n", 
               flights[index].departure_time.hours,
               flights[index].departure_time.minutes);
        printf("Время прилета: %02d:%02d\n",
               flights[index].arrival_time.hours,
               flights[index].arrival_time.minutes);
        printf("Направление: %s\n", flights[index].destination);
        printf("Марка самолета: %s\n", flights[index].aircraft_model);
        printf("Расстояние: %d км\n", flights[index].distance);
        printf("========================================\n");
    }
    else
    {
        printf("Нет данных о рейсах. Сначала введите данные.\n");
    }
}

/*
 * Функция 3: ВЫВОД ВСЕХ РЕЙСОВ ДЛЯ ОПРЕДЕЛЁННОЙ МАРКИ САМОЛЁТА
 */
void print_flights_by_model(AIRPLANE2 flights[], int count)
{
    char model[MAX_STRING];
    int i;
    int found = 0;
    
    if (count <= 0)
    {
        printf("❌ Нет данных о рейсах. Сначала введите данные.\n");
        return;
    }
    
    printf("Введите марку самолета: ");
    safe_string_input(model, MAX_STRING);
    
    printf("\n✈️  РЕЙСЫ МАРКИ %s ✈️\n", model);
    printf("================================================================================\n");
    printf("%-6s %-12s %-12s %-15s %-12s %-10s\n", 
           "№", "Вылет", "Прилет", "Направление", "Расстояние", "Скорость");
    printf("================================================================================\n");
    
    for (i = 0; i < count; i++)
    {
        if (strcasecmp_custom(flights[i].aircraft_model, model) == 0)
        {
            printf("%-6d %02d:%02d      %02d:%02d      %-15s %-8d км  %-6.1f км/ч\n",
                   flights[i].flight_number,
                   flights[i].departure_time.hours,
                   flights[i].departure_time.minutes,
                   flights[i].arrival_time.hours,
                   flights[i].arrival_time.minutes,
                   flights[i].destination,
                   flights[i].distance,
                   calculate_speed(flights[i]));
            found++;
        }
    }
    
    if (found == 0)
    {
        printf("❌ Рейсы марки %s не найдены\n", model);
    }
    else
    {
        printf("================================================================================\n");
        printf("✅ Найдено рейсов: %d\n", found);
    }
}

/*
 * Функция 4: ПОИСК РЕЙСА С МИНИМАЛЬНЫМ РАССТОЯНИЕМ
 */
int find_min_distance_flight(AIRPLANE2 flights[], int count)
{
    int i;
    int min_index = 0;
    int min_distance;
    
    if (count <= 0)
    {
        return -1;
    }
    
    min_distance = flights[0].distance;
    min_index = 0;
    
    for (i = 1; i < count; i++)
    {
        if (flights[i].distance < min_distance)
        {
            min_distance = flights[i].distance;
            min_index = i;
        }
    }
    
    return min_index;
}

/*
 * Функция 4 (вывод): ВЫВОД РЕЙСА С МИНИМАЛЬНЫМ РАССТОЯНИЕМ
 */
void print_min_distance_flight(AIRPLANE2 flights[], int count)
{
    int index;
    
    index = find_min_distance_flight(flights, count);
    
    if (index >= 0)
    {
        printf("\n  РЕЙС С МИНИМАЛЬНЫМ РАССТОЯНИЕМ \n");
        printf("========================================\n");
        printf("Расстояние: %d км\n", flights[index].distance);
        printf("Номер рейса: %d\n", flights[index].flight_number);
        printf("Время вылета: %02d:%02d\n", 
               flights[index].departure_time.hours,
               flights[index].departure_time.minutes);
        printf("Время прилета: %02d:%02d\n",
               flights[index].arrival_time.hours,
               flights[index].arrival_time.minutes);
        printf("Направление: %s\n", flights[index].destination);
        printf("Марка самолета: %s\n", flights[index].aircraft_model);
        printf("Скорость: %.1f км/ч\n", calculate_speed(flights[index]));
        printf("========================================\n");
    }
    else
    {
        printf("Нет данных о рейсах. Сначала введите данные.\n");
    }
}

/*
 * Функция 5: ПОДСЧЕТ КОЛИЧЕСТВА РЕЙСОВ ДЛЯ КАЖДОГО НАПРАВЛЕНИЯ
 */
void count_flights_by_destination(AIRPLANE2 flights[], int count)
{
    int i, j;
    int dest_count = 0;
    char destinations[MAX_FLIGHTS][MAX_STRING];
    int counts[MAX_FLIGHTS] = {0};
    int found;
    
    if (count <= 0)
    {
        printf("❌ Нет данных о рейсах. Сначала введите данные.\n");
        return;
    }
    
    /* Собираем уникальные направления и считаем количество */
    for (i = 0; i < count; i++)
    {
        found = 0;
        
        /* Проверяем, есть ли уже такое направление в списке */
        for (j = 0; j < dest_count; j++)
        {
            if (strcasecmp_custom(flights[i].destination, destinations[j]) == 0)
            {
                counts[j]++;
                found = 1;
                break;
            }
        }
        
        /* Если направление новое, добавляем его */
        if (!found)
        {
            strcpy(destinations[dest_count], flights[i].destination);
            counts[dest_count] = 1;
            dest_count++;
        }
    }
    
    /* Выводим результаты */
    printf("\n  КОЛИЧЕСТВО РЕЙСОВ ПО НАПРАВЛЕНИЯМ \n");
    printf("========================================\n");
    printf("%-20s %10s\n", "Направление", "Количество");
    printf("----------------------------------------\n");
    
    for (i = 0; i < dest_count; i++)
    {
        printf("%-20s %10d\n", destinations[i], counts[i]);
    }
    printf("========================================\n");
    printf("✅ Всего направлений: %d\n", dest_count);
    printf("✅ Всего рейсов: %d\n", count);
}
