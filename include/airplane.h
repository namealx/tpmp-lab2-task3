/* airplane.h */
/* Автор: Юранов Никита, группа 12 */

#ifndef AIRPLANE_H
#define AIRPLANE_H

/*
 * ИНТЕРФЕЙС МОДУЛЯ РАБОТЫ С АВИАРЕЙСАМИ
 * 
 * Содержит определение структуры AIRPLANE2 и прототипы всех функций.
 */

#include <stdio.h>

/* Константы */
#define MAX_FLIGHTS 20        /* Максимальное количество рейсов */
#define MAX_STRING 50         /* Максимальная длина строк */
#define SECONDS_IN_HOUR 3600  /* Секунд в часе */

/*
 * Структура для хранения времени
 */
typedef struct {
    int hours;      /* Часы (0-23) */
    int minutes;    /* Минуты (0-59) */
} Time;

/*
 * ОСНОВНАЯ СТРУКТУРА: AIRPLANE2
 * Содержит все поля согласно варианту 23
 */
typedef struct {
    int flight_number;              /* № Авиарейса */
    Time departure_time;            /* Время вылета */
    Time arrival_time;              /* Время прилета */
    char destination[MAX_STRING];   /* Направление */
    char aircraft_model[MAX_STRING]; /* Марка самолета */
    int distance;                   /* Расстояние */
} AIRPLANE2;

/*
 * ПРОТОТИПЫ ФУНКЦИЙ
 */

/*	
 * Функция 1: Создание массива записей (не менее 12)
 * Параметры: flights - массив структур для заполнения
 *            count - указатель для сохранения количества записей
 */
void create_flights(AIRPLANE2 flights[], int *count);

/*
 * Вспомогательная функция: вычисление скорости
 * Параметры: flight - структура с данными о рейсе
 * Возвращает: среднюю скорость в км/ч
 */
double calculate_speed(AIRPLANE2 flight);

/*
 * Функция 2: Поиск рейса с максимальной скоростью
 * Параметры: flights - массив структур
 *            count - количество рейсов
 * Возвращает: индекс рейса с максимальной скоростью
 */
int find_max_speed_flight(AIRPLANE2 flights[], int count);

/*
 * Функция 2 (вывод): Вывод рейса с максимальной скоростью
 * Параметры: flights - массив структур
 *            count - количество рейсов
 */
void print_max_speed_flight(AIRPLANE2 flights[], int count);

/*
 * Функция 3: Вывод всех рейсов для определённой марки самолёта
 * Параметры: flights - массив структур
 *            count - количество рейсов
 */
void print_flights_by_model(AIRPLANE2 flights[], int count);

/*
 * Функция 4: Поиск рейса с минимальным расстоянием
 * Параметры: flights - массив структур
 *            count - количество рейсов
 * Возвращает: индекс рейса с минимальным расстоянием
 */
int find_min_distance_flight(AIRPLANE2 flights[], int count);

/*
 * Функция 4 (вывод): Вывод рейса с минимальным расстоянием
 * Параметры: flights - массив структур
 *            count - количество рейсов
 */
void print_min_distance_flight(AIRPLANE2 flights[], int count);

/*
 * Функция 5: Подсчет количества рейсов для каждого направления
 * Параметры: flights - массив структур
 *            count - количество рейсов
 */
void count_flights_by_destination(AIRPLANE2 flights[], int count);

#endif /* AIRPLANE_H */
