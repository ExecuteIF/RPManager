#pragma once

/**
 * 
 *			 __  __ _ _          ______ ___
 *			|  \/  (_) |        |  ____(_)=|=========//===[_]
 *			| \  / |_| | ___   _| |__   _| | ___  \\//
 *			| |\/| | | |/ / | | |  __| | | |/ _ \  ||
 *			| |  |=| |   <| |_| | |    | | |  __/  ||
 *			|_|  |_|_|_|\_\\__,_|_|    |_|_|\___|  []
 * 
 * 
 *			FILE NAME	:	mikufile.h
 *			ENCODING	:	UTF-8 BOM
 *			START		:	2022/06/26 4:28 P.M. 
 *			#1 Completed:	2022/07/14 8:30 P.M.
 *			#1 Fixes	:	2022/07/14 9:05 P.M.
 *			#1 Releases	:	2022/07/14 9:06 P.M.
 * 			PROGRAMMER	:	{"Hwnd", "Executif", "Ginkx", "Redactedsxp", "Sprincle", "ChiYy", "Caspase"}
 * 			TYPE		:	Open-Source
 * 			LICENSE		:	GNU LGPL 3.0 (http://www.gnu.org/licenses/lgpl-3.0.html)
 * 
**/

/* < ! - - settings - - ! > */
#define MIKUFILE_BUFFER_MAXN					1024
#define MIKUFILE_CONFIG_FILE_DELIMITER			'='

// #undef NDEBUG
#define NDEBUG

/* < ! - - definitions - - ! > */
// nothing here currently ¯\_(ツ)_/¯

/* < ! - - includes - - ! > */
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

/* < ! - - functions - - ! > */
// namespace for internal functions
namespace __scallion__
{
	/// <summary>
	/// memory error
	/// </summary>
	/// <param name="reason">leave empty for "memory access violation"</param>
	inline void mav(std::string reason = "")
	{
		if (reason == "") {
			std::cerr << "Memory Access Violation.";
		}
		else {
			std::cerr << reason;
		}
		exit(0x0001bf52);
	}
}

// namespace exports

// the namespace's name was "mf" (Miku File). but for ergonomic considerations,
// (the key 'm' is too far from 'f'),
// we use mk instead
namespace mk
{
	// config file (*.cfg, *.ini, *.properties, etc.)
	/**
	 *
	 * file format:
	 * ```cfg
	 * # this a note
	 * # following line is a empty line
	 *
	 * # this is a bool
	 * bool = true
	 *
	 * # this is a int
	 * int = 39
	 *
	 * # this is a string
	 * string = "mikufile"
	 * ```
	 *
	**/
	class config {
	public:
		/// <summary>
		/// open a file
		/// </summary>
		/// <param name="path">the file path</param>
		/// <returns>success: false; fail: true</returns>
		bool open(std::string path)
		{
			this->fin.open(path);
			if (this->fin.fail()) {
				return true;
			}

			this->fileTmp = path;
			this->fileTmp += ".tmp";
			this->filePath = path;

			// analyze tmp file dir
			int s = int(path.size());
			for (int i = int(path.size() - 1); i >= 0; --i) {
				if (path[i] == '/' || path[i] == '\\') {
					break;
				}
				s = i;
			}

			// set file name
			this->fileName = "";
			for (int i = s; i < path.size(); ++i) {
				this->fileName += path[i];
			}

			return false;
		}
		/// <summary>
		/// close the opening file
		/// </summary>
		void close()
		{
			this->fin.flush();
			this->fin.close();
		}
		inline bool is_open()
		{
			return this->fin.is_open();
		}
		inline bool fail()
		{
			return this->fin.fail();
		}

		/// <summary>
		/// read a bool from specified file
		/// </summary>
		/// <param name="key">the keyname, if not exist, return false</param>
		/// <returns></returns>
		bool readBool(std::string key)
		{
			// get data
			const fdat data = getStrByKey(key);

			// error
			if (data.failed || data.notFound) {
				return false;
			}
			
			// return result
			if (data.value == "true") {
				return true;
			}
			return false;
		}
		/// <summary>
		/// read a double from specified file
		/// </summary>
		/// <param name="key">the key name, if not exist, return false</param>
		/// <returns></returns>
		double readNum(std::string key)
		{
			// init
			double ans;

			// get data
			const fdat data = getStrByKey(key);

			// error
			if (data.failed || data.notFound) {
				return 0;
			}

			// get value
			std::istringstream stream(data.value);
			stream >> ans;
			return ans;
		}
		/// <summary>
		/// read a string from specified file
		/// </summary>
		/// <param name="key">the key name, if not exist, return false</param>
		/// <returns></returns>
		std::string readStr(std::string key)
		{
			// init
			std::string tmp;

			// get data
			const fdat data = getStrByKey(key);

			// error
			if (data.failed || data.notFound) {
				return "";
			}

			// process string
			for (int i = 1; i < data.value.length() - 1; ++i) {
				tmp += data.value[i];
			}
			return tmp;
		}

		/// <summary>
		/// write data into the specified file
		/// </summary>
		/// <param name="key">the specified key</param>
		/// <param name="data">the data</param>
		/// <returns>success: true; fail: false</returns>
		bool writeBool(std::string key, bool data)
		{
			// init
			char buffer[MIKUFILE_BUFFER_MAXN] = "\0";

			// get data
			const fdat fdata = getStrByKey(key);

			if (fdata.failed) {
				return true;
			}

			// not found
			if (fdata.notFound) {
				// not found, ios::app to the end
				this->close();
				this->fin.open(this->filePath, std::ios::app);
				fin << key + MIKUFILE_CONFIG_FILE_DELIMITER + (data == true ? "true" : "false");
				this->close();
				this->open(this->filePath);
			}
			else {
				// found, del the line and instead with the new one
				delLn(fdata.line, key + MIKUFILE_CONFIG_FILE_DELIMITER + (data == true ? "true" : "false"));
			}
			return false;
		}
		/// <summary>
		/// write data into the specified file
		/// </summary>
		/// <param name="key">the specified key</param>
		/// <param name="data">the data</param>
		/// <returns>success: true; fail: false</returns>
		bool writeNum(std::string key, double data)
		{
			// init
			char buffer[MIKUFILE_BUFFER_MAXN] = "\0";

			// get data
			const fdat fdata = getStrByKey(key);

			if (fdata.failed) {
				return true;
			}

			// not found
			if (fdata.notFound) {
				// not found, ios::app to the end
				this->close();
				this->fin.open(this->filePath, std::ios::app);
				fin << key + MIKUFILE_CONFIG_FILE_DELIMITER + std::to_string(data);
				this->close();
				this->open(this->filePath);
			}
			else {
				// found, del the line and instead with the new one
				delLn(fdata.line, key + MIKUFILE_CONFIG_FILE_DELIMITER + std::to_string(data));
			}
			return false;
		}
		/// <summary>
		/// write data into the specified file
		/// </summary>
		/// <param name="key">the specified key</param>
		/// <param name="data">the data</param>
		/// <returns>success: true; fail: false</returns>
		bool writeStr(std::string key, std::string data)
		{
			// init
			char buffer[MIKUFILE_BUFFER_MAXN] = "\0";

			// get data
			const fdat fdata = getStrByKey(key);

			if (fdata.failed) {
				return true;
			}

			// not found
			if (fdata.notFound) {
				// not found, ios::app to the end
				this->close();
				this->fin.open(this->filePath, std::ios::app);
				fin << key + MIKUFILE_CONFIG_FILE_DELIMITER + "\"" + data + "\"";
				this->close();
				this->open(this->filePath);
			}
			else {
				// found, del the line and instead with the new one
				delLn(fdata.line, key + MIKUFILE_CONFIG_FILE_DELIMITER + "\"" + data + "\"");
			}
			return false;
		}
	private:
		std::fstream fin;		// file handler
		std::string fileTmp;	// temp file path
		std::string filePath;	// original file path
		std::string fileName;	// original file name
		/// <summary>
		/// file data used for "getStrByKey" returning
		/// </summary>
		struct fdat {
			bool failed = false;
			bool notFound = false;
			int line;
			int keyStart;
			int keyEnd;
			int valueStart;
			int valueEnd;
			std::string value;
		};
		/// <summary>
		/// get the value(string) by specified key.
		/// </summary>
		/// <param name="key">the key</param>
		/// <returns>the value(string)</returns>
		fdat getStrByKey(std::string key)
		{
			// init
			resetPointer();
			char buffer[MIKUFILE_BUFFER_MAXN];
			int key_s, key_e;
			int val_s, val_e;
			int pos_equ;
			std::string buffer_cpy;
			std::string tmp;
			int ln = 0;

			// read
			bool flag; // is note
			while (!this->fin.eof()) {
				// init
				++ln;
				flag = false;
				key_e = -1;
				std::memset(buffer, '\0', sizeof(buffer));

				// get line
				this->fin.getline(buffer, sizeof(buffer));
				buffer_cpy = buffer;

				// skip notes and empty lines
				if (buffer_cpy.empty()) {
					continue;		// empty lines
				}

				for (int i = 0; i < buffer_cpy.size(); ++i) {
					if (buffer[i] == '#') {
						break;		// note line
					}
					if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '#') {
						flag = true;
						key_s = i;
						break;		// content line
					}
				}
				if (!flag) {
					continue;		// skip note lines and invalid lines
				}
				flag = false;

				// get key interr.
				for (int i = key_s; i < buffer_cpy.size(); ++i) {
					if (buffer[i] == MIKUFILE_CONFIG_FILE_DELIMITER)
					{
						flag = true;
						pos_equ = i;
						key_e = i;
						break;
					}
				}
				if (!flag) {
					continue;		// doesn't contain a correct key2value config
				}
				flag = false;

				// get the real end-key
				for (--key_e; key_e > key_s; --key_e) {
					if (buffer[key_e] != ' ' && buffer[key_e] != '\t') {
						break;
					}
				}

				// get the key
				tmp = "";
				for (int i = key_s; i <= key_e; ++i) {
					tmp += buffer[i];
				}

				// check the key
				if (tmp != key) {
					continue;	// key doesn't match 
				}

				// get value interr.
				for (int i = pos_equ + 1; i < buffer_cpy.size(); ++i) {
					if (buffer[i] != ' ' && buffer[i] != '\t') {
						flag = true;
						val_s = i;
						break;
					}
				}
				if (!flag) {
					return { true, false, 0,0,0,0,0, "" };	// valid key but invalid value
				}
				flag = false;

				// get the real end-key
				for (int i = int(buffer_cpy.size() - 1); i > val_s; --i) {
					if (buffer[i] != ' ' && buffer[i] != '\t') {
						flag = true;
						val_e = i;
						break;
					}
				}
				if (!flag) {
					return { true, false, 0, 0, 0, 0, 0, "" };	// valid key but invalid value
				}

				// get the value
				tmp = "";
				for (int i = val_s; i <= val_e; ++i) {
					tmp += buffer[i];
				}

				return { false, false, ln, key_s, key_e, val_s, val_e, tmp}; // found
			}
			return { false, true, 0,0,0,0,0, ""}; // not found
		}
		/// <summary>
		/// remove the data of a line
		/// </summary>
		/// <param name="line">the line number, start from 0</param>
		void delLn(int line, std::string instead = "", bool useEndlingWhenDeleting = true)
		{
			// the program starts from '0', but counter starts from '1'.
			--line;

			// init
			std::fstream temp;

			// open tmp file
			temp.open(this->fileTmp, std::ios::ate | std::ios::out);
			if (temp.fail()) {
				assert(0);
				__scallion__::mav("Failed to open temp file, check disk or access tier");
			}

			// init2
			char buffer[MIKUFILE_BUFFER_MAXN];
			resetPointer();

			// copy file #1
			for (int i = 0; i < line ; ++i) {
				this->fin.getline(buffer, sizeof(buffer));
				temp << buffer << "\n";
			}

			// ignore current line
			this->fin.getline(buffer, sizeof(buffer));
			// output instead
			temp << instead;
			// output empty line
			if (useEndlingWhenDeleting) {
				temp << "\n";
			}

			// copy file #2
			for (int i = line + 1; !fin.eof(); ++i) {
				this->fin.getline(buffer, sizeof(buffer));
				temp << buffer;
				if (!(buffer[0] == '\0' && fin.peek() == EOF)) {
					temp << "\n";
				}
			}

			// end
			temp.flush();
			temp.close();

			// overwrite original file
			int result = 0;
			this->fin.close();
			result += remove(this->filePath.c_str());
			result += rename(this->fileTmp.c_str(), this->fileName.c_str());
			if (result != 0) {
				assert(0);
				__scallion__::mav("Failed to overwrite file: " + filePath);
			}
			remove(this->fileTmp.c_str());

			// re-open file
			if (this->open(this->filePath)) {
				assert("Failed to re-open file");
				__scallion__::mav("Failed re-open file: " + filePath);
			}
			return;
		}
		/// <summary>
		/// goto a line
		/// </summary>
		/// <param name="lineNum">the specified line number</param>
		void gotoLn(int lineNum = -1)
		{
			char buffer[MIKUFILE_BUFFER_MAXN];

			resetPointer();

			if (lineNum == -1) {
				while (fin.peek() != EOF) {
					this->fin.getline(buffer, sizeof(buffer));
				}
				return;
			}
			else {
				for (int i = 0; i < lineNum; ++i) {
					this->fin.getline(buffer, sizeof(buffer));
				}
				return;
			}
		}
		/// <summary>
		/// go back to the start of file
		/// </summary>
		inline void resetPointer()
		{
			this->fin.clear();
			this->fin.seekg(0, std::ios::beg);
		}
	};
}
