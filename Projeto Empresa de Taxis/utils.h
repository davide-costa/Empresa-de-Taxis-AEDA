/**
*
* @file
* @brief Contains all functions declarations that we consider of general utility.
*
*/

#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#include <sstream>
#include <Windows.h>
#include <algorithm>

#include "Date.h"
#include "TimeStamp.h"
#include "Taxi.h"

using namespace std;

/**
*
* @brief Clears the console windows screen, i. e., erases all the characters on it.
*
*/
void ClearScreen();
/**
*
* @brief Removes all the spaces (character ' ') from a phrase. Since it is a frase, it leaves one space between each word (but no more than 1).
* @param phrase The phrase from which to remove the spaces from. (passed by reference to act also as a return)
*
*/
void RemoveSpacesFromPhrase(string &phrase);
/**
*
* @brief Removes all the spaces (character ' ') from a word. Since it is a word, it removes every ' ' from the string, because a word must not have spaces between its characters.
* @param phrase The word from which to remove the spaces from. (passed by reference to act also as a return)
*
*/
void RemoveSpacesFromWord(string &word);
/**
*
* @brief Verifies if two characters are equal, case insensitively.
* @param a The first character to verify
* @param b The second character to verify
* @return true if they are equal; false if they are not equal.
*
*/
bool CharsAreEqualCaseInsensitive(unsigned char a, unsigned char b);
/**
*
* @brief Verifies if two strings are equal, case insensitively. (uses the CharsAreEqualCaseInsensitive function).
* @param a The first string to verify
* @param b The second string to verify
* @return true if they are equal; false if they are not equal.
*
*/
bool StringsAreEqualCaseInsensitive(string a, string b);
/**
*
* @brief Reads an unsigned int from the user. Does not return until the user introduces a valid input, i. e., an input that doesn't cause a failure in the cin stream. Keeps asking for input until while it doesn't have the desired one. Ignores all remaining input to ensure that if the user introduced something that is not part of the wanted input, it won't compromise the next attempt to read information from the user.
* @param error_msg The appropriate error message to display when it fails to read the input from the user. Since this functions is generic, it can be called from any context. It recieves this pameter to show an error message that is appropriate in the context it was called from.
* @return The unsigned int value read from the user.
*
*/
unsigned int ReadUnsignedInt(string error_msg);
/**
*
* @brief Reads a string from the user. Does not return until the user introduces a valid input, i. e., an input that doesn't cause a failure in the cin stream. Keeps asking for input until while it doesn't have the desired one.
* @param error_msg The appropriate error message to display when it fails to read the input from the user. Since this functions is generic, it can be called from any context. It recieves this pameter to show an error message that is appropriate in the context it was called from.
* @return The string object read from the user.
*
*/
string ReadString(string error_msg);
/**
*
* @brief Reads a floating point number from the user. Does not return until the user introduces a valid input, i. e., an input that doesn't cause a failure in the cin stream. Keeps asking for input until while it doesn't have the desired one. Ignores all remaining input to ensure that if the user introduced something that is not part of the wanted input, it won't compromise the next attempt to read information from the user.
* @param error_msg The appropriate error message to display when it fails to read the input from the user. Since this functions is generic, it can be called from any context. It recieves this pameter to show an error message that is appropriate in the context it was called from.
* @return The floating point number read from the user.
*
*/
float ReadFloat(string error_msg);
/**
*
* @brief Reads a Date object from the user. Does not return until the user introduces a valid input, i. e., an input that doesn't cause a failure in the cin stream or an invalid date (something like 50/11/2016, or one of other many bad formats). Keeps asking for input until while it doesn't have the desired one.
* @param Date The Date read from user (returns by reference).
*
*/
void ReadDate(Date &Date);
/**
*
* @brief Reads a TimeStamp object from the user. Does not return until the user introduces a valid input, i. e., an input that doesn't cause a failure in the cin stream or an invalid time stamp (something like 50/11/2016 30:51:21, or one of other many bad formats). Keeps asking for input until while it doesn't have the desired one.
* @param time The TimeStamp read from user (returns by reference).
*
*/
void ReadTimeStamp(TimeStamp &time);
/**
*
* @brief Reads a LicensePlate object from the user. Does not return until the user introduces a valid input, i. e., an input that doesn't cause a failure in the cin stream or an invalid license plate (something like ABC-54-BC 50/2015, or one of other many bad formats). Keeps asking for input until while it doesn't have the desired one.
* @param plate The LicensePlate read from user (returns by reference).
*
*/
void ReadLicensePlate(LicensePlate &plate);
/**
*
* @brief Reads an answer of type "yes or no" (case insensitively) from the user. Does not return until the user introduces a valid input, i. e., an input that doesn't cause a failure in the cin stream or an invalid answer (something that is not "sim" or "nao" (in upper or lower case)). Keeps asking for input until while it doesn't have the desired one.
* @return The answer of the user. Return true if the user inputed "sim"; false if the user input "no".
*
*/
bool ReadYesOrNo();
/**
*
* @brief Converts a Date object element (day, month or year) to string format and makes it neat. Making it neat means adding a "0" to it if it is less than 10, in order to make it appear in a user friendly way.
* @param elem The element of the Date to return in string and neat format.
* @return A string with the element of the Date in neat format.
*
*/
string MakeNeatDate(int elem);
/**
*
* @brief Gets the Current date from windows using the function GetLocalTime and fills the Date object it recieves as parameter with that information.
* @param windows_date The Date object to fill with the current Windows date. (returns by reference)
*
*/
void GetDateFromWindows(Date &windows_date);
/**
*
* @brief Gets the Current timestamp (time and date) from windows using the function GetLocalTime and fills the TimeStamp object it recieves as parameter with that information.
* @param windows_date The TimeStamp object to fill with the current Windows date and time. (returns by reference)
*
*/
void GetTimeStampFromWindows(TimeStamp &windows_time);
/**
*
* @brief Verifies if the year passed as parameter is bissextile.
* @param year The year to verify if is bissextile
* @return true if the year is bissextile; false if it is not
*
*/
bool Bissextile(int year);
/**
*
* @brief Verifies if a Date object is valid. (something like 50/11/2016 is not valid, or one of many other bad formats (also considers bissextile and non-bissextile year cases to verify the date)).
* @param Date The Date object to verify the validity of
* @return true if the date is valid; false if it is not valid
*
*/
bool IsDateValid(const Date &Date);
/**
*
* @brief Verifies if a TimeStamp object is valid. (something like 50/11/2016 45:32:70 is not valid, or one of many other bad formats (also considers bissextile and non-bissextile year cases to verify the date)).
* @param time The TimeStamp object to verify the validity of
* @return true if the TimeStamp is valid; false if it is not valid
*
*/
bool IsTimeStampValid(const TimeStamp &time);
/**
*
* @brief Verifies if a LicensePlate object is valid. (something like ABC-43-32 is not valid, or one of many other bad formats).
* @param license_plate The LicensePlate object to verify the validity of
* @return true if the LicensePlate is valid; false if it is not
*
*/
bool IsLicensePlateValid(const LicensePlate &license_plate);
/**
*
* @brief Verifies if a NIF (Numero de Identificação Fiscal) (unsigned long) is valid. It uses modular aritmetic to verify the validity.
* @param nif The NIF number to verify the validity of
* @return true if the NIF is valid; false if it is not
*
*/
bool IsNifValid(unsigned long nif);
/**
*
* @brief Extracts a date from a string it recieves as parameter and fills the Date object it recieves as parameter with the information of a date.
* @param date The Date object to be filled with the information extracted from the string.
* @param date_str The string to extract the date from.
* @return true if the Date contained in the string is valid; false if it is not valid
*
*/
bool ExtractDate(Date &date, string date_str);
/**
*
* @brief Computes the temporary file name of a file, given its original name. It changes its extension, for example if the original file was "customers_p.txt", the temporary file name is "customer_p.tmp". If the file had no extension, it simply adds the extension tmp.
* @param original_fn The name of the original file.
* @return the name of the temporary file.
*
*/
string GetTmpFileName(string original_fn);
/**
*
* @brief Computes the difference in minutes between two TimeStamp objects.
* @param time1 The first TimeStamp.
* @param time2 The second TimeStamp (that will be subtracted to the first, in minutes).
* @return a number that represents the difference in minutes between the two timestamps.
*
*/
unsigned int ComputeDifferenceInMinutes(const TimeStamp &time1, const TimeStamp &time2);
/**
*
* @brief Converts a number of seconds to a time stamp string in hours, minutes and seconds (HMS) (easier to read by the user) (returns a string something like 3 hours, 26 minutes and 34 seconds) (Effectively calls GetHMSFromSeconds and returns a string containing the information got from this function. (Only fills in the necessary elements, i. e., if the hours are 0, does not show the word hours in the return string).
* @return a string containing the a time stamp easier to read by the user represented in the argument total_seconds. (returns a string something like 3 hours, 26 minutes and 34 seconds)
*
*/
string MakeNeatTimeStampFromSeconds(time_t total_seconds);
/**
*
* @brief Converts a number of seconds to a time stamp in hours, minutes and seconds (HMS) (easier to read by the user)
* @param total_seconds The total number of seconds to be converted to an HMS time stamp.
* @param hours The total number of hours that total_seconds contains (returns by reference).
* @param minutes The number of minutes that total_seconds contains (cannot exceed 59) (returns by reference).
* @param minutes The number of seconds that total_seconds contains (cannot exceed 59) (returns by reference).
*
*/
void GetHMSFromSeconds(time_t total_seconds, unsigned int &hours, unsigned int &minutes, unsigned int &seconds);
