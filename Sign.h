#pragma once
#include <string>

#include "Zodiac.h"

namespace Signs {
	class Sign {
		const int DEFAULT_BIRTHDAY[3] = {1, 1, 1900};

		std::string name;
		std::string lastName;
		Zodiac zodiac;
		int birthday[3];

		void setZodiac(int birthday[3]);
		bool validateAndSetBirthday(int birthday[3]);
		static std::string trim(const std::string& str);
	public:

		Sign();
		Sign(const std::string& name, const std::string& lastName, int birthday[3]);
		Sign(const Sign& other);
		~Sign() = default;

		Sign& operator =(const Sign& other);
		bool operator ==(const Sign& other) const;
		bool operator <(const Sign& other) const;
		bool operator >(const Sign& other) const;

		const std::string& getName() const;
		const std::string& getLastName() const;
		const Zodiac getZodiac() const;
		int* getBirthday() const;

		void setName(const std::string& name);
		void setLastName(const std::string& lastName);
		void setBirthday(int birthday[3]);

		friend std::ostream& operator <<(std::ostream& os, const Sign& s);
		friend std::istream& operator >>(std::istream& is, Sign& s);
	};
}