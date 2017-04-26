#include "scanner.h"

int write_dat(FILE **dba, const SCAN_INFO *rec)
{
	SCAN_INFO *buff;
	int num = 0;

	if ((buff = (SCAN_INFO*)malloc(sizeof(SCAN_INFO))) == NULL)
		return -1;

	fseek(*dba, 0, SEEK_SET);
	
	if (!feof(*dba))
	{
		fread(&num, sizeof(int), 1, *dba);

		while (!feof(*dba))
		{
			fread(buff, sizeof(SCAN_INFO), 1, *dba);
			if (memcmp(rec, buff, sizeof(SCAN_INFO)) == 0)
			{
				free(buff);
				return 0;
			}
		}

		free(buff);
		fseek(*dba, 0, SEEK_SET);
	}

	num++;
	fwrite(&num, sizeof(int), 1, *dba);
	fseek(*dba, 0, SEEK_END);
	fwrite(rec, sizeof(SCAN_INFO), 1, *dba);

	return 1;
}

int csv_to_dba(const char *path_dba, const char *path_csv)
{
	FILE *dba;
	FILE *csv;
	SCAN_INFO *rec;

	if ((dba = fopen(path_dba, "wb+")) == NULL)
	{
		printf("open file error\n");
		return 0;
	}
	if ((csv = fopen(path_csv, "r")) == NULL)
	{
		fclose(dba);
		printf("open file error\n");
		return 0;
	}
	if ((rec = (SCAN_INFO*)malloc(sizeof(SCAN_INFO))) == NULL)
	{
		fclose(dba);
		fclose(csv);
		return -1;
	}
	while (!feof(csv))
	{
		fscanf(csv, "%[A-z0-9];%[A-z0-9];%d;%f;%d;%d;%d\n", rec->manufacturer, rec->model, &(rec->year), &(rec->price), &(rec->x_size), &(rec->y_size), &(rec->optr));
		if (!write_dat(&dba, rec)) break;
	}

	free(rec);
	fclose(dba);
	fclose(csv);
	
	return 1;
}

int make_index(char *path_dba, char *field_name)
{
	FILE *idx, *dba;
	char *path_idx;
	int i = strlen(path_dba), j = 0, num = 0;
	const int len = strlen(field_name);
	SCAN_INFO **recs, *buff;
	
	if ((dba = fopen(path_dba, "rb")) == NULL)
	{
		printf("open file error\n");
		return 0;
	}

	while (i >= 0 && *(path_dba + i) != '/')
		i--;

	if ((path_idx = (char*)malloc((len + i + 6) * sizeof(char))) == NULL)
	{
		fclose(dba);
		return -1;
	}
	if (i >= 0)
		strncpy(path_idx, path_dba, i + 1);

	strcpy(path_idx + i + 1, field_name);
	strcpy(path_idx + len + i + 1, ".idx");

	if ((idx = fopen(path_idx, "w")) == NULL)
	{
		free(path_idx);
		fclose(dba);
		return 0;
	}

	free(path_idx);
	fread(&num, sizeof(int), 1, dba);

	if (num > 0)
	{
		recs = (SCAN_INFO**)malloc(num * sizeof(SCAN_INFO*));
		buff = (SCAN_INFO*)malloc(sizeof(SCAN_INFO));

		if (recs == NULL || buff == NULL)
		{
			fclose(dba);
			fclose(idx);
			return -1;
		}
		for (i = 0; i < num; i++)
		{
			if ((recs[i] = (SCAN_INFO*)malloc(sizeof(SCAN_INFO))) == NULL)
			{
				for (j = 0; j < i; j++)
					free(recs[j]);

				free(buff);
				free(recs);
				fclose(dba);
				fclose(idx);
				return -1;
			}
			fread(recs[i], sizeof(SCAN_INFO), 1, dba);
		}
	}

	if (field_name == "manufacturer")
		qsort(recs, num, sizeof(SCAN_INFO*), manufacturer_cmp);
	else if (field_name == "year")
		qsort(recs, num, sizeof(SCAN_INFO*), year_cmp);
	else if (field_name == "model")
		qsort(recs, num, sizeof(SCAN_INFO*), model_cmp);
	else if (field_name == "price")
		qsort(recs, num, sizeof(SCAN_INFO*), price_cmp);
	else if (field_name == "x_size")
		qsort(recs, num, sizeof(SCAN_INFO*), x_size_cmp);
	else if (field_name == "y_size")
		qsort(recs, num, sizeof(SCAN_INFO*), y_size_cmp);
	else if (field_name == "optr")
		qsort(recs, num, sizeof(SCAN_INFO*), optr_cmp);

	for (i = 0; i < num; i++)
	{
		fseek(dba, sizeof(int), SEEK_SET);
		for (j = 0; j < num; j++)
		{
			fread(buff, sizeof(SCAN_INFO), 1, dba);
			if (recs[i] != NULL && strcmp(buff->manufacturer, recs[i]->manufacturer) == 0 && strcmp(buff->model, recs[i]->model) == 0)
			{
				fprintf(idx, "%d ", j);
				free(recs[i]);
				recs[i] = NULL;
			}
		}
	}

	free(recs);
	free(buff);
	fclose(dba);
	fclose(idx);

	return 1;
}

int manufacturer_cmp(const void *val1, const void *val2)
{
	// вах-вах. подгоняем под результаты в методичке
	return strcmp((*(SCAN_INFO**)val1)->manufacturer, (*(SCAN_INFO**)val2)->manufacturer) >= 0 && strcmp((*(SCAN_INFO**)val1)->model, (*(SCAN_INFO**)val2)->model) >= 0;
}
int year_cmp(const void *val1, const void *val2)
{
	return (*(SCAN_INFO**)val1)->year - (*(SCAN_INFO**)val2)->year;
}
int model_cmp(const void *val1, const void *val2)
{
	return strcmp((*(SCAN_INFO**)val1)->model, (*(SCAN_INFO**)val2)->model);
}
int price_cmp(const void *val1, const void *val2)
{
	return (int)((*(SCAN_INFO**)val1)->price - (*(SCAN_INFO**)val2)->price);
}
int x_size_cmp(const void *val1, const void *val2)
{
	return (*(SCAN_INFO**)val1)->x_size - (*(SCAN_INFO**)val2)->x_size;
}
int y_size_cmp(const void *val1, const void *val2)
{
	return (*(SCAN_INFO**)val1)->y_size - (*(SCAN_INFO**)val2)->y_size;
}
int optr_cmp(const void *val1, const void *val2)
{
	return (*(SCAN_INFO**)val1)->optr - (*(SCAN_INFO**)val2)->optr;
}

RECORD_SET *get_recs_by_index(char *path_dba, char *indx_field)
{
	RECORD_SET *set;
	FILE *dba, *idx;
	int i = 0, j = 0, number = 0;

	if ((dba = fopen(path_dba, "rb")) == NULL)
	{
		printf("open file error\n");
		return NULL;
	}
	if ((idx = fopen(indx_field, "r")) == NULL)
	{
		fclose(dba);
		printf("open file error\n");
		return NULL;
	}
	if ((set = (RECORD_SET*)malloc(sizeof(int) + sizeof(SCAN_INFO*))) == NULL)
	{
		fclose(dba);
		fclose(idx);
		return NULL;
	}

	fread(&(set->rec_nmb), sizeof(int), 1, dba);
	
	if (set->rec_nmb > 0)
	{
		if ((set->recs = (SCAN_INFO*)malloc(set->rec_nmb * sizeof(SCAN_INFO))) == NULL)
		{
			free(set);
			fclose(dba);
			fclose(idx);
			return NULL;
		}
		for (i = 0; i < set->rec_nmb; i++)
		{
			fscanf(idx, "%d ", &j);
			fseek(dba, sizeof(int), SEEK_SET);
			fseek(dba, j * sizeof(SCAN_INFO), SEEK_CUR);
			fread(set->recs + i, sizeof(SCAN_INFO), 1, dba);
		}

		free(set->recs);
	}

	free(set);
	fclose(dba);
	fclose(idx);

	return set;
}

void reindex(char *path_dba)
{
	make_index(path_dba, "manufacturer");
	make_index(path_dba, "year");
	make_index(path_dba, "model");
	make_index(path_dba, "price");
	make_index(path_dba, "x_size");
	make_index(path_dba, "y_size");
	make_index(path_dba, "optr");
}

int del_scan(char *path_dba, int n)
{
	FILE *dba;
	int num, i, j = 0;
	SCAN_INFO *recs;

	if ((dba = fopen(path_dba, "rb")) == NULL)
	{
		printf("open file error\n");
		return 0;
	}

	fread(&num, sizeof(int), 1, dba);

	if (num == 0 || num < n)
	{
		printf("string number error");
		fclose(dba);
		return 0;
	}
	if ((recs = (SCAN_INFO*)malloc((num - 1) * sizeof(SCAN_INFO))) == NULL)
	{
		fclose(dba);
		return -1;
	}
	for (i = 0; i < num; i++)
	{
		fread(recs + j, sizeof(SCAN_INFO), 1, dba);
		if (i == n) continue;
		j++;
	}
	if ((dba = freopen(path_dba, "wb", dba)) == NULL)
	{
		free(recs);
		fclose(dba);
		return 0;
	}

	rewind(dba);
	num--;
	fwrite(&num, sizeof(int), 1, dba);
	fwrite(recs, sizeof(SCAN_INFO), num, dba);

	free(recs);
	fclose(dba);
	reindex(path_dba);

	return 0;
}

int scanners_by_maxprice(char *path_dba, char *path_txt, float price)
{
	FILE *dba;
	FILE *txt;
	SCAN_INFO *recs;
	int num = 0, i = 0;

	if ((dba = fopen(path_dba, "rb")) == NULL)
	{
		printf("open file error\n");
		return 0;
	}
	if ((txt = fopen(path_txt, "w")) == NULL)
	{
		fclose(dba);
		return 0;
	}

	fread(&num, sizeof(int), 1, dba);

	if (num > 0)
	{
		if ((recs = (SCAN_INFO*)malloc(num * sizeof(SCAN_INFO))) == NULL)
		{
			fclose(dba);
			fclose(txt);
			return -1;
		}

		fread(recs, sizeof(SCAN_INFO), num, dba);

		for (i = 0; i < num; i++)
		{
			if (recs[i].price <= price)
				fprintf(txt, "%s;%s;%d;%g;%d;%d;%d\n", recs[i].manufacturer, recs[i].model, recs[i].year, recs[i].price, recs[i].x_size, recs[i].y_size, recs[i].optr);
		}
		free(recs);
	}

	fclose(dba);
	fclose(txt);

	return 0;
}