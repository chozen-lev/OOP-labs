#include <stdio.h>
#include "scanner.h"

int main()
{
	csv_to_dba("Scanners.dba", "Scanners.csv");
    reindex("Scanners.dba");
	get_recs_by_index("Scanners.dba", "manufacturer.idx");
	del_scan("Scanners.dba", 3);
	scanners_by_maxprice("Scanners.dba", "pricelist.txt", 300.0);
	return 0;
}