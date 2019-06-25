#include "utils.h"


//Clears the console
void ClearScreen()
{
	COORD upperLeftCorner = { 0,0 };
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);
}
//------------------------------------------------------------------------------
//Receives a phrase and removes all the unnecessary spaces from it
void RemoveSpacesFromPhrase(string &phrase)
{
	//If the recieved string is empty, do nothing to it and return immediately
	if (phrase.length() == 0)
		return;

	//Remove all spaces until the first non-space char is reached; if the string gets emptied during the removal process, return
	while (phrase[0] == ' ')
	{
		phrase.erase(0, 1);
		if (phrase.length() == 0)
			return;
	}

	//Remove the next unncessary spaces in the middle of the text until the pre-last char of the string is reached
	int last_pos = (int)phrase.length() - 1;
	for (int i = 0; i < last_pos; i++)
		if ((phrase[i] == ' ') && (phrase[i + 1] == ' '))
		{
			phrase.erase(i, 1);
			i--;
			last_pos--;
		}

	//Remove all the spaces in the end of the string
	if (phrase[phrase.length() - 1] == ' ')
		phrase.erase(phrase.length() - 1, 1);
}
//------------------------------------------------------------------------------
//Receives a word and removes all the unnecessary spaces from it
void RemoveSpacesFromWord(string &word)
{
	for (unsigned int i = 0; i < word.length(); i++)
		if (word[i] == ' ')
		{
			word.erase(i, 1);
			i--;
		}
}
//------------------------------------------------------------------------------
//Compares two chars case insensitively
bool CharsAreEqualCaseInsensitive(unsigned char a, unsigned char b)
{
	return tolower(a) == tolower(b);
}
//------------------------------------------------------------------------------
//Compares two chars case insensitively
bool StringsAreEqualCaseInsensitive(string a, string b)
{
	if (a.length() != b.length())
		return false;

	return equal(a.begin(), a.end(), b.begin(), CharsAreEqualCaseInsensitive);
}
//-----------------------------------------Input Validation Functions------------------------------------------------
//Reads a value of type double from user
//Does not return anything while the user does not introduce the intended input
//Has a call_id to display the appropriate error message, depending on what type of data it was called to read
unsigned int ReadUnsignedInt(string error_msg)
{
	int i;
	cin >> i;
	while (cin.fail())
	{
		if (cin.eof())
			cin.clear();
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		cout << endl << error_msg;
		cin >> i;
	}
	//Ignore the next characters inputed, to make sure the cin buffer is clean before being used by another function
	cin.ignore(INT_MAX, '\n');
	return i;
}
//------------------------------------------------------------------------------
//Reads a value of type string from user
//Does not return anything while the user does not introduce the intended input
//Has a call_id to display the appropriate error message, depending on what type of data it was called to read
string ReadString(string error_msg)
{
	string str;
	getline(cin, str);
	RemoveSpacesFromPhrase(str);
	while (cin.fail() || str.empty())
	{
		if (cin.fail())
			if (cin.eof())
				cin.clear();
			else
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
		cout << endl << error_msg;
		getline(cin, str);
		RemoveSpacesFromPhrase(str);
	}
	return str;
}
//------------------------------------------------------------------------------
//Reads a value of type double from user
//Does not return anything while the user does not introduce the intended input
//Has a call_id to display the appropriate error message, depending on what type of data it was called to read
float ReadFloat(string error_msg)
{
	float flt;
	cin >> flt;
	while (cin.fail())
	{
		if (cin.eof())
			cin.clear();
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		cout << endl << error_msg;
		cin >> flt;
	}
	//Ignore the next characters inputed, to make sure the cin buffer is clean before being used by another function
	cin.ignore(INT_MAX, '\n');
	return flt;
}
//------------------------------------------------------------------------------
//Receives an empty Date class, and fills it with a date read from user
void ReadDate(Date &Date)
{
	cout << "Introduza na forma dd/mm/yyyy: ";
	string error_msg = "Ocorreu um erro ao ler a data que introduziu. Por favor, tente novamente, introduzindo uma data valido: ";
	string date_str = ReadString(error_msg);
	while (!ExtractDate(Date, date_str))
	{
		cout << endl << "A data introduzida e invalida. Por favor, tente novamente, introduzindo uma data valida: ";
		date_str = ReadString(error_msg);
	}
}
//------------------------------------------------------------------------------
//Reads a value of type TimeStamp from user
//Does not return anything while the user does not introduce the intended input
void ReadTimeStamp(TimeStamp &time)
{
	bool wrong_input = true;
	string input_str;
	istringstream iss;
	string error_msg = "Ocorreu um erro ao ler a data/hora que introduziu. Por favor, tente novamente, introduzindo uma data/hora valida: ";
	while (wrong_input)
	{
		input_str = ReadString(error_msg);
		iss.str(input_str);
		try
		{
			iss >> time;
			wrong_input = false;
		}
		catch (TimeStamp::ErrorReadingTimeStampFromStream &error)
		{
			cout << "Ocorreu um erro ao ler a data/hora que introduziu. Por favor, tente novamente, introduzindo uma data/hora valida: ";
		}
		catch (TimeStamp::InvalidTimeStamp &error)
		{
			cout << "A data/hora que introduziu e invalida. Por favor, tente novamente, introduzindo uma data/hora valida: ";
		}

		iss.clear();
	}
}
//------------------------------------------------------------------------------
//Reads a LicensePlate from user and checks it
void ReadLicensePlate(LicensePlate &plate)
{
	bool wrong_input = true;
	string input_str;
	istringstream iss;
	string error_msg = "Ocorreu um erro ao ler a matricula que introduziu. Por favor, tente novamente, introduzindo uma matricula valida: ";
	while (wrong_input)
	{
		input_str = ReadString(error_msg);
		iss.str(input_str);
		try
		{
			iss >> plate;
			wrong_input = false;
		}
		catch (LicensePlate::ErrorReadingLicensePlate &error)
		{
			cout << "Ocorreu um erro ao ler a matricula que introduziu. Por favor, tente novamente, introduzindo uma matricula valida: ";
		}
		catch (LicensePlate::InvalidLicensePlate &error)
		{
			cout << "A matricula que introduziu e invalida. Por favor, tente novamente, introduzindo uma matricula valida: ";
		}

		iss.clear();
	}
}
//------------------------------------------------------------------------------
//Reads an yes or no answer from the user and checks it
bool ReadYesOrNo()
{
	string error_msg = "Ocorreu um erro ao ler a resposta que introduziu. Por favor, tente novamente, introduzindo uma reposta valida: ";
	string answer = ReadString(error_msg);

	while (StringsAreEqualCaseInsensitive(answer, "sim") || StringsAreEqualCaseInsensitive(answer, "nao"))
	{
		answer = ReadString(error_msg);
	}

	if (answer == "sim")
		return true;
	else
		return false;
}
//------------------------------------------------------------------------------
//Receives an integer (member of the date) and returns a neat string with the correct date format
//For example if the recieved day is 1, it returns "01"
string MakeNeatDate(int elem)
{
	ostringstream return_oss;
	if (elem < 10)
		return_oss << "0" << elem;
	else
		return_oss << elem;

	string return_str = return_oss.str();
	return return_str;
}
//------------------------------------------------------------------------------
//Get the date from Windows Local Time
void GetDateFromWindows(Date &windows_date)
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	windows_date.SetDay(time.wDay);
	windows_date.SetMonth(time.wMonth);
	windows_date.SetYear(time.wYear);
}
//------------------------------------------------------------------------------
//Get the timestamp from Windows Local Time
void GetTimeStampFromWindows(TimeStamp &windows_time)
{
	GetDateFromWindows(windows_time);//taking advantage of polimorfism (the function above fills the date part of the timestamp
	SYSTEMTIME time;
	GetLocalTime(&time);
	windows_time.SetHours(time.wHour);
	windows_time.SetMinutes(time.wMinute);
	windows_time.SetSeconds(time.wSecond);
}
//------------------------------------------------------------------------------
//Receives an integer representing the year; returns true if the year is bissextile or false if its not
bool Bissextile(int year)
{
	if (year % 4 == 0 && year % 100 != 0)
		return true;

	if (year % 400 == 0)
		return true;

	return false;
}
//------------------------------------------------------------------------------
//Receives 3 integers representing a date; returns true if the date is valid; returns false if its not valid
bool IsDateValid(const Date &Date)
{
	int day = Date.GetDay();
	int month = Date.GetMonth();
	int year = Date.GetYear();

	if (day <= 0 || day > 31 || month <= 0 || month > 12 || year < 0)
		return false;

	if (month == 2)
		if (Bissextile(year))
		{
			if (day > 29)
				return false;
		}
		else
			if (day > 28)
				return false;

	if (month == 4 || month == 6 || month == 9 || month == 11)
		if (day > 30)
			return false;

	return true;
}
//------------------------------------------------------------------------------
//Receives 6 integers representing a TimeStamp; returns true if the TimeStamp is valid; returns false if its not valid
bool IsTimeStampValid(const TimeStamp &time)
{
	Date date_from_timestamp = time; //taking advantage of slicing problem
	if (!IsDateValid(date_from_timestamp))
		return false;

	int hours = time.GetHours();
	int minutes = time.GetMinutes();
	int seconds = time.GetSeconds();

	if (hours < 0 || hours > 23)
		return false;

	if (minutes < 0 || minutes > 59)
		return false;

	if (seconds < 0 || seconds > 59)
		return false;

	return true;
}
//------------------------------------------------------------------------------
//Receives a license plate and verifies its validity; returns true if the license plate is valid; returns false otherwise
bool IsLicensePlateValid(const LicensePlate &license_plate)
{
	if (license_plate.GetFirst().length() != 2)
		return false;

	if (license_plate.GetSecond().length() != 2)
		return false;

	if (license_plate.GetThird().length() != 2)
		return false;

	if (license_plate.GetYear() <= 0)
		return false;

	if (license_plate.GetMonth() <= 0 || license_plate.GetMonth() > 12)
		return false;

}
//------------------------------------------------------------------------------
//Receives a NIF and returns true if it's valid; false otherwise
bool IsNifValid(unsigned long nif)
{
	//check length
	string nif_str = to_string(nif);
	if (nif_str.length() != 9)
		return false;

	//check first digit
	string first_digit = "1 2 5 6 8 9";
	if (first_digit.find(nif_str[0]) == string::npos)
		return false;

	//check mod11
	int curr_number;
	int soma = 0;
	for (int i = 9; i >= 2; i--)
	{
		curr_number = pow(10, i - 1);
		soma += (nif / curr_number) * i;
		nif -= (nif / curr_number) * curr_number;  // subtracts the current number * 10 raised to the power of its position
	}

	int remainder_11 = soma % 11;
	if (remainder_11 == 0)
		if (nif == 0 || nif == 1)
			return true;
		else
			return false;
	else
		if (nif = 11 - remainder_11)
			return true;
		else
			return false;
}
//------------------------------------------------------------------------------
//Receives a string containing and extracts the date from it, and fills a Date class with that information; removes all spaces from the string to avoid any errors
bool ExtractDate(Date &Date, string date_str)
{
	istringstream date_iss;
	char ch;
	//Declaring all the integers that will be extracted from the date string; they all are initialized as -1 for future error checking
	int day = -1;
	int month = -1;
	int year = -1;

	date_iss.str(date_str);
	date_iss >> day >> ch;
	date_iss >> month >> ch;
	date_iss >> year;

	Date.SetDay(day);
	Date.SetMonth(month);
	Date.SetYear(year);

	if (!IsDateValid(Date))
		return false;

	return true;
}
//------------------------------------------------------------------------------
//Receives a file name (with or without an extension) and returns the temporary file name (with the extension .tmp)
string GetTmpFileName(string original_fn)
{
	string temp_fn;
	//Get the position of the extension
	int ext_pos = original_fn.find_last_of(".");

	//If the file has no extension, ignore it
	if (ext_pos != string::npos)
		temp_fn = original_fn.substr(0, ext_pos - 1);
	else
		temp_fn = original_fn;

	//Append the extension ".tmp" to the temporary file name
	temp_fn.append(".tmp");
	return temp_fn;
}
//------------------------------------------------------------------------------
unsigned int ComputeDifferenceInMinutes(const TimeStamp &time1, const TimeStamp &time2)
{
	unsigned int time1_seconds = time1.GetHours() * 3600 + time1.GetMinutes() * 60 + time1.GetSeconds();
	unsigned int time2_seconds = time2.GetHours() * 3600 + time2.GetMinutes() * 60 + time2.GetSeconds();

	unsigned int difference_seconds, difference_minutes;
	if (time2_seconds < time1_seconds)
	{
		difference_seconds = time2_seconds + ((60 * 60 * 24) - time1_seconds);
	}
	else
		difference_seconds = time2_seconds - time1_seconds;

	difference_minutes = difference_seconds / 60;

	return difference_minutes;
}
//------------------------------------------------------------------------------
string MakeNeatTimeStampFromSeconds(time_t total_seconds)
{
	string neat_time_stamp;
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;
	GetHMSFromSeconds(total_seconds, hours, minutes, seconds);

	if (hours != 0)
		neat_time_stamp.append(to_string(hours) + " horas");

	if (hours == 0)
		neat_time_stamp = to_string(minutes) + " minutos";
	else if (minutes != 0)
		neat_time_stamp.append(", " + to_string(minutes) + " minutos");

	if (hours == 0 && minutes == 0)
		neat_time_stamp = to_string(seconds) + " segundos";
	else if (seconds != 0)
		neat_time_stamp.append(" e " + to_string(seconds) + " segundos");

	return neat_time_stamp;
}
//------------------------------------------------------------------------------
void GetHMSFromSeconds(time_t total_seconds, unsigned int &hours, unsigned int &minutes, unsigned int &seconds)
{
	seconds = total_seconds % 60;
	total_seconds /= 60;
	minutes = total_seconds % 60;
	total_seconds /= 60;
	hours = total_seconds;
}