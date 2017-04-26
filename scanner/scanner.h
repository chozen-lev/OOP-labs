#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char manufacturer[127];	// изготовитель
	int year;				// год изготовления
	char model[128];		// наименование модели
	float price;			// цена
	int x_size;				// горизонтальный размер области сканирования
	int y_size;				// вертикальный размер области сканирования
	int optr;				// оптическое разрешение
} SCAN_INFO;

typedef struct {
	int rec_nmb;		// number of records
	SCAN_INFO *recs;	// records 
} RECORD_SET;

int write_dat(FILE **dba, const SCAN_INFO *rec); // 1
int csv_to_dba(const char *path_dba, const char *path_csv); // 2

int manufacturer_cmp(const void *val1, const void *val2);
int year_cmp(const void *val1, const void *val2);
int model_cmp(const void *val1, const void *val2);
int price_cmp(const void *val1, const void *val2);
int x_size_cmp(const void *val1, const void *val2);
int y_size_cmp(const void *val1, const void *val2);
int optr_cmp(const void *val1, const void *val2);

int make_index(char *path_dba, char *field_name); // 3
RECORD_SET *get_recs_by_index(char *path_dba, char *indx_field); // 4
void reindex(char *path_dba); // 5
int del_scan(char *path_dba, int n); // 6
int scanners_by_maxprice(char *path_dba, char *path_txt, float price); // 7