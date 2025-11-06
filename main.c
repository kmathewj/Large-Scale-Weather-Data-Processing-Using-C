/* Term Project V12 - Final
 * By Kelin Mathew Jacob and Waafiq Mazarik
 * April 2 2024
 * Version Changes:
 * 	Comments fixed for submission
 * IMPORTANT NOTES:
 * 	Final version
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define size 1000

int main(void) {
	
	char row[size]; // row of data
	char *token; // pointer to tokenized value (values seperated by commas in a row)
	int year; // year, or first value in the row
	double total; // total of monthly averages
	double high = 0; //highest temp
	double low = 5000; //lowest temp (5000 chosen arbitrarily for comparsion)
	
// Question 1 - Yearly avg temp from 1760 to 2015
	// Question 5 - From yearly average temperatures, determine the hottest and coldest years
	// Question 6 - Generate GNUPlot data File for yearly temperatures 1760 - 2015
	// Question 7 - Genearte GNUPlot data file for yearly temperatures for both the 19th and 20th century

	FILE *in = fopen("/GlobalTemperatures.csv", "r"); //Open file for Q1
	FILE *out = fopen("/q6.dat", "w"); //Create file to export data for Q6
	FILE *out2 = fopen("/q7part1.dat", "w"); //Create file to export data for Q7 part 1 (19th century)
	FILE *out3 = fopen("/q7part2.dat", "w"); //Create file to export data for Q7 part 2 (20th century)
	
	int hottestYear; // Stores hottest year (Q5)
	int coldestYear; // Stores coldest year (Q5)
	
	while(year != 1760){ // Skips lines until year 1760
		fgets(row, sizeof(row), in); 
		token = strtok(row, ",");
		year = atoi(token);
	} // line of month 1 of 1760 is already read in

	printf("QUESTION 1:\n"); // Table headings for Q1
	printf("Year        Avg. Temp\n"); 
	printf("----        ---------\n");
	
	while(!feof(in)){ // Runs for all 256 years 1760 - 2015
		for(int j=1; j<=12; ++j){ // Sums up averages for the 12 months in one year
			year = atoi(token);
			token = strtok(NULL, ","); // Reads monthly land avg. temp
			total += atof(token); // Adds monthly avg. to total
			fgets(row, sizeof(row), in); // Gets next line
			token = strtok(row, ",");
		}
		printf("%d %12.3lf\n", year, total/12); // Prints year and yearly avg. temp, which is the total for that year divided by the 12 months, to terminal
		
		// For Q5 - Determines hottest year 
		if(total/12 > high){ // If avg. for that year is hotter, replace hottest year
			high = total/12; // New hottest year
			hottestYear = year;
		}
		
		// For Q5 - Determines coldest year 
		if(total/12 < low){ // If avg. for that year is colder, replace hottest year
			low = total/12;
			coldestYear = year; // New coldest year
		}
		
		// For Question 6 - Write out year and yearly averages to file
		fprintf(out, "%d %12.3lf\n", year, total/12); 
		
		// For Question 7 - Write out century 19 and century average to file
		if(year >= 1800 && year <= 1899){ // If years are in 19th century
			fprintf(out2, "%d %12.3lf\n", year%100, total/12); 
		}
		
		// For Question 7 - Write out century 20 and century average to file
		if(year >= 1900 && year <= 1999){ // If years are in 20th century
			fprintf(out3, "%d %12.3lf\n", year%100, total/12);
		}
		
		total = 0; // Reset total before moving to next year
	}
	
	fclose(in); // Close file for question 1
	fclose(out); // Close file for question 6
	fclose(out2); // Close file for question 7 Part 1
	fclose(out3); // Close file for question 7 Part 2
	
// Question 2 - Century avgs for 18th, 19th, 20th, 21st

	in = fopen("/GlobalTemperatures.csv", "r"); // Open file for Q2 (to reset to start)
	double month_counter = 0; // Counts months being iterated through
	
	while(year != 1760){ // Skips lines until year 1760
		fgets(row, sizeof(row), in); 
		token = strtok(row, ",");
		year = atoi(token);
	} // Line of month 1 of 1760 is already read in
	
	printf("\nQUESTION 2:\n"); // Q2 table headings
	printf("Century     Avg. Temp\n");
	printf("-------     ---------\n");
	
	while (year <= 1799){ // 18th century average
		for (int i = 0; i < 12; i ++){ // For all 12 months in a year
				token = strtok(NULL, ","); // Read monthly avg land temp
				total += atof(token); // Add to century long total avg temp sum
				month_counter ++; // Add one to months counted
				fgets(row, sizeof(row), in);  // Go to next line
				token = strtok(row, ","); 
				year = atoi(token); // Grab next year
			}
		} printf("18          %.3lf\n", total/(month_counter)); // Calcuate and prints the century average (sum of monthly averages divided by number of months)
		total = 0; // Reset total
		month_counter = 0; // Reset months counted
		
	while (year <= 1899){ // 19th century average
		for (int i = 0; i < 12; i ++){
				token = strtok(NULL, ",");
				total += atof(token);
				month_counter ++;
				fgets(row, sizeof(row), in); 
				token = strtok(row, ",");
				year = atoi(token);
			}
		} printf("19          %.3lf\n", total/(month_counter)); 
		total = 0;
		month_counter = 0; 
	
	while (year <= 1999){ //20th century average
		for (int i = 0; i < 12; i ++){
				token = strtok(NULL, ",");
				total += atof(token);
				month_counter ++;
				fgets(row, sizeof(row), in); 
				token = strtok(row, ",");
				year = atoi(token);
			}
		} printf("20          %.3lf\n", total/(month_counter)); 
		total = 0;
		month_counter = 0;
	
	while (!feof(in)){ // 21st century average, using EOF function as file ends after 2015
		for (int i = 0; i < 12; i ++){
				token = strtok(NULL, ",");
				total += atof(token);
				month_counter ++;
				fgets(row, sizeof(row), in); 
				token = strtok(row, ",");
				year = atoi(token);
			}
		} printf("21          %.3lf\n", total/(month_counter));
		total = 0;
		month_counter = 0; 

	fclose(in); // Close file for question 2

// Question 3 - Monthly avg for all 12 months between 1900 and 2015

	in = fopen("/GlobalTemperatures.csv", "r"); // Open file for Q3 (to reset to start)
	double month_sum[12]; // Array containig 12 monthly sums over the time period
	double yr_counter = 0; // Counts number of years iterated through
	
	
	while(year != 1900){ // Skips lines until year 1900
		fgets(row, sizeof(row), in); 
		token = strtok(row, ",");
		year = atoi(token);
	} // Line of month 1 of 1900 is already read in
	

	while (!feof(in)){ // Runs until 2015, or end of file
		for (int i = 0; i < 12; i ++){ // For all 12 months
			token = strtok(NULL, ","); // Get monthly avg
			month_sum[i] += atof(token); // Add that monthly average to its dedicated month sum in the array, index i = 0 being january
			fgets(row, sizeof(row), in); 
			token = strtok(row, ",");
			year = atoi(token);
			}yr_counter ++; // Update year counter
				
		}
		
	printf("\nQUESTION 3:\n"); // Q3 table header
	printf("Month       Avg. Temp\n");
	printf("--------    ---------\n");
	for (int i = 0; i < 1; i ++){
			printf("January     %.3lf\n", month_sum[i]/yr_counter); // Average for that month which is the sum for the month divided by the total years iterated thtough
			printf("February    %.3lf\n", month_sum[i+1]/yr_counter); // Add 1 to index i to get to the next month sum in the array
			printf("March       %.3lf\n", month_sum[i+2]/yr_counter);
			printf("April       %.3lf\n", month_sum[i+3]/yr_counter);
			printf("May         %.3lf\n", month_sum[i+4]/yr_counter);
			printf("June        %.3lf\n", month_sum[i+5]/yr_counter);
			printf("July        %.3lf\n", month_sum[i+6]/yr_counter);
			printf("August      %.3lf\n", month_sum[i+7]/yr_counter);
			printf("September   %.3lf\n", month_sum[i+8]/yr_counter);
			printf("October     %.3lf\n", month_sum[i+9]/yr_counter);
			printf("November    %.3lf\n", month_sum[i+10]/yr_counter);
			printf("December    %.3lf\n", month_sum[i+11]/yr_counter);
		}
		
	fclose(in); // Close file for question 3
	
// Question 4 - Hottest and coldest month

	in = fopen("/GlobalTemperatures.csv", "r"); // Open file for Q3 (to reset to start)
	
	// Reset high and low values from Q1
	high = 0; // Highest temperature
	low = 50; // Lowest temperature (50 chosen arbitrarily for comparsion)
	
	char temp[50]; // Temporary string that stores the month and year
	char hottestMonth[8]; // Hottest month and respective year in YYYY-MM form
	char coldestMonth[8]; // Coldest month and respective year in YYYY-MM form
	
	while(year != 1760){ // Skips lines until year 1760
		fgets(row, sizeof(row), in); 
		token = strtok(row, ",");
		year = atoi(token);
	} // Month 1 of 1760 is already read in
	
	printf("\nQUESTION 4:\n");
	
	strncpy(temp, token, 7); // Condition - If January 1760 is the coldest/hottest month
	
	while(!feof(in)){
		for(int i=1; i<=12;i++){ // Checks every month of a year
			token = strtok(NULL, ","); // Land avg. temperature
			
			if(atof(token) > high){ // New high temperature
				high = atof(token); 
				strncpy(hottestMonth, temp, 7); 
			}
			
			if(atof(token) < low){ // New low temperature
				low = atof(token);
				strncpy(coldestMonth, temp, 7); 
			}
			
			fgets(row, sizeof(row), in);
			token = strtok(row, ",");
			strncpy(temp, token, 7); 
		}
	}
	
	printf("Hottest Month: %s\n", hottestMonth);
	printf("Coldest Month: %s\n", coldestMonth);
	
	fclose(in); // Close input file for question 4
	
// Question 5 - Hottest and Colest Year (see Q1 for determination)

	printf("\nQUESTION 5:\n");
	printf("Hottest Year: %d\n", hottestYear); // Prints hottest year
	printf("Coldest Year: %d\n", coldestYear); // Prints coldest year
	
// Question 6 - GNUPlot of yrly avg between 1760 and 2015 (see Q1 for data file creation)

// Question 7 - GNUPlot of yrly avg land temps for 19th and 20th century (see Q1 for data file creation)

// Question 8 - GNUPlot of Yrly average, minmum, and maximum temperatures between 1850 and 2015

	in = fopen("/GlobalTemperatures.csv", "r"); // Open file for Q8 (to reset to start)
	out = fopen("/q8.dat", "w"); // Open data file for Q8 to export data out
	double minsum, maxsum; // Sums of minimum and maximum monthly averages
	
	while(year != 1850){ // Skips lines until year 1850
		fgets(row, sizeof(row), in); 
		token = strtok(row, ",");
		year = atoi(token);
	} // Line of month 1 of 1850 is already read in
	
	total = 0; // Reset total
	while (!feof(in)){ // Runs until 2015, or end of file
		for (int i = 0; i < 12; i ++){ // For 12 months in a year
				token = strtok(NULL, ","); // Grabs monthly avg
				total += atof(token); // Add to yearly total
				token = strtok(NULL, ","); // Skip column
				token = strtok(NULL, ","); // Grab max monthly avg
				maxsum += atof(token); // Add to yearly max total
				token = strtok(NULL, ","); // Skip column
				token = strtok(NULL, ","); // Grab min monthly avg
				minsum += atof(token); // Add to yearly min total
				fgets(row, sizeof(row), in); // Gets next year
				token = strtok(row, ",");
				year = atoi(token);
			}
			fprintf(out, "%d %12.3lf %12.3lf %12.3lf\n", year-1, total/12.0, minsum/12.0, maxsum/12.0); // Writes out: year (-1 bcs year updated before data written out), avg, minavg, maxavg to data file
			total = minsum = maxsum = 0; // Reset running sums
	}
		
	fclose(in); // Close input file for question 8
	fclose(out); // Close output file for question 8
	
// Question 9 - GNUPlot of average, minmum, and maximum for 19th, 20th, and 21st centuries
	
	in = fopen("/GlobalTemperatures.csv", "r"); // Open file for Q9 (to reset to start)
	out = fopen("/q9.dat", "w"); // Open data file for Q8 to export data out
	
	while(year != 1850){ // Skips lines until year 1850
		fgets(row, sizeof(row), in); 
		token = strtok(row, ",");
		year = atoi(token);
	} // Line of month 1 of 1850 is already read in
	
	month_counter = 0;
	while (year <= 1899){ // 19th century average, from 1850
		for (int i = 0; i < 12; i ++){
				token = strtok(NULL, ","); // Grabs monthly avg
				total += atof(token); // Add to running avg total
				token = strtok(NULL, ","); // Skip column
				token = strtok(NULL, ","); // Gab max monthly avg
				maxsum += atof(token); // Add to running max total
				token = strtok(NULL, ","); // Skip column
				token = strtok(NULL, ","); // Grab min monthly avg
				minsum += atof(token); // Add to running min total
				month_counter ++; // Update months iterated through
				fgets(row, sizeof(row), in); 
				token = strtok(row, ",");
				year = atoi(token); // Grabs year
			} 
		} fprintf(out, "19 %12.3lf %12.3lf %12.3lf\n", total/month_counter, minsum/month_counter, maxsum/month_counter); // Writes to file: 19(th century), avg, minavg, max,avg - avg determined by divding by number of months iterated through in the century
		total = minsum = maxsum = 0; // Reset running sums
	
	month_counter = 0;
	while (year <= 1999){ // 20th century average
		for (int i = 0; i < 12; i ++){
				token = strtok(NULL, ","); 
				total += atof(token);
				token = strtok(NULL, ","); 
				token = strtok(NULL, ","); 
				maxsum += atof(token); 
				token = strtok(NULL, ","); 
				token = strtok(NULL, ","); 
				minsum += atof(token);
				month_counter ++;
				fgets(row, sizeof(row), in); 
				token = strtok(row, ",");
				year = atoi(token);
			} 
		} fprintf(out, "20 %12.3lf %12.3lf %12.3lf\n", total/month_counter, minsum/month_counter, maxsum/month_counter); // Writes to file: 20(th century), avg, minavg, max,avg
		total = minsum = maxsum = 0;
		
	month_counter = 0;
	while (!feof(in)){ // 21st century average, until 2015, or end of file
		for (int i = 0; i < 12; i ++){
				token = strtok(NULL, ","); 
				total += atof(token); 
				token = strtok(NULL, ",");
				token = strtok(NULL, ","); 
				maxsum += atof(token); 
				token = strtok(NULL, ","); 
				token = strtok(NULL, ","); 
				minsum += atof(token); 
				month_counter ++;
				fgets(row, sizeof(row), in); 
				token = strtok(row, ",");
				year = atoi(token);
			} 
		} fprintf(out, "21 %12.3lf %12.3lf %12.3lf\n", total/month_counter, minsum/month_counter, maxsum/month_counter); // Writes to file: 21(st century), avg, minavg, max,avg
		total = minsum = maxsum = 0; 
		
		fclose(in); // Close file for Q9
		fclose(out); // Close output file for Q9

// Question 10 - GNU plot of average monthly land temperature with error bars btw 2000 and 2015

	in = fopen("/GlobalTemperatures.csv", "r"); // Open file for Q10 (to reset to start)
	out = fopen("/q10.dat", "w"); // Open data file for Q10 to export data out
	
	while(year != 2000){ // Skips lines until year 2000
		fgets(row, sizeof(row), in); 
		token = strtok(row, ",");
		year = atoi(token);
	} // Line of month 1 of 2000 is already read in

	for (int i = 0; i < 12; i ++){
		month_sum[i] = 0.0;
		} //Reset month_sum array
	double unc_sum[12]; // Array containing sums of uncertainities for each of the 12 months over period iterated though
	yr_counter = 0; // Counts number of years iterated through
	
	while (!feof(in)){ // Runs until 2015, or end of file
		for (int i = 0; i < 12; i ++){ 
			token = strtok(NULL, ","); // Grabs monthly avg
			month_sum[i] += atof(token); // Add to yearly total for the month, with index i = 0 being january
			token = strtok(NULL, ","); // Grab uncertainty for the month
			unc_sum[i] += atof(token); // Add to yearly uncertainity total for the month, with index i = 0 being january
			fgets(row, sizeof(row), in); // Gets next year
			token = strtok(row, ",");
			year = atoi(token);
			} yr_counter ++; // Update year counter	
	}
	
	for (int i = 0; i < 12; i ++){
		fprintf(out, "%d %12.3lf %12.3lf\n",i+1, month_sum[i]/yr_counter, unc_sum[i]/yr_counter); // Writes to file average for each month which is the sum for the month divided by the total years iterated through
		}
	
	fclose(in); // Close file for Q10
	fclose(out); // Close file for Q11
	
// Question 11 - GNUPlot of yearly avg land temp and land+ocean temps

	in = fopen("/GlobalTemperatures.csv", "r"); // Open file for Q11 (to reset to start)
	out = fopen("/q11.dat", "w"); // Open data file for Q11 to export data out
	
	while(year != 1850){ // Skips lines until year 1850
		fgets(row, sizeof(row), in); 
		token = strtok(row, ",");
		year = atoi(token);
	} // Line of month 1 of 1850 is already read in
	
	total = 0; // Reset total
	double oceansum;
	while (!feof(in)){ // Runs until 2015, or end of file
		for (int i = 0; i < 12; i ++){ // For 12 months in a year
				token = strtok(NULL, ","); // Grabs monthly avg
				total += atof(token); // Add to yearly land avg total
				token = strtok(NULL, ","); // Skip column
				token = strtok(NULL, ","); // Skip column
				token = strtok(NULL, ","); // Skip column
				token = strtok(NULL, ","); // Skip column
				token = strtok(NULL, ","); // Skip column
				token = strtok(NULL, ","); // Skip column
				oceansum += atof(token); // Add to yearly ocean+land avg total
				fgets(row, sizeof(row), in); // Gets next year
				token = strtok(row, ",");
				year = atoi(token);
			}	
			fprintf(out, "%d %12.3lf %12.3lf\n",year - 1,total/12.0, oceansum/12.0); // Writes out to file, year (-1 because year is updated before being wirtten), land avg, ocean+land avg
			total = oceansum = 0; // reset sums for next year		
	}
	
	fclose(in); // Close file for Q11
	fclose(out); // Close output file for Q11
	
	return 0;	
}
