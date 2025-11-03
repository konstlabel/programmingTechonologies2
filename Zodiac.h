#pragma once

#include <iostream>

namespace Signs {
	enum class Zodiac {
		Aries,			//     March 21 -	  April 19
		Taurus,			//     April 20 -       May	20
		Gemini,			//       May 21 -      June 20
		Cancer,			//      June 21 -      July 22
		Leo,			//      July 23 -    August 22
		Virgo,			//    August 23 - September 22
		Libra,			// September 23 -   October	22
		Scorpio,		//   October 23 -  November	21
		Sagittarius,	//  November 22 -  December	21
		Capricorn,		//  December 22 -   January	19
		Aquarius,		//   January 20 -  February	18
		Pisces			//  February 19 -     March	20
	};

    inline std::string to_string(Zodiac z) {
        switch (z) {
        case Zodiac::Aries:        return "Aries";
        case Zodiac::Taurus:       return "Taurus";
        case Zodiac::Gemini:       return "Gemini";
        case Zodiac::Cancer:       return "Cancer";
        case Zodiac::Leo:          return "Leo";
        case Zodiac::Virgo:        return "Virgo";
        case Zodiac::Libra:        return "Libra";
        case Zodiac::Scorpio:      return "Scorpio";
        case Zodiac::Sagittarius:  return "Sagittarius";
        case Zodiac::Capricorn:    return "Capricorn";
        case Zodiac::Aquarius:     return "Aquarius";
        case Zodiac::Pisces:       return "Pisces";
        default:                   return "Unknown";
        }
    }

    inline Zodiac from_string(const std::string& zodiac) {
        if (zodiac == "Aries")        return Zodiac::Aries;
        if (zodiac == "Taurus")       return Zodiac::Taurus;
        if (zodiac == "Gemini")       return Zodiac::Gemini;
        if (zodiac == "Cancer")       return Zodiac::Cancer;
        if (zodiac == "Leo")          return Zodiac::Leo;
        if (zodiac == "Virgo")        return Zodiac::Virgo;
        if (zodiac == "Libra")        return Zodiac::Libra;
        if (zodiac == "Scorpio")      return Zodiac::Scorpio;
        if (zodiac == "Sagittarius")  return Zodiac::Sagittarius;
        if (zodiac == "Capricorn")    return Zodiac::Capricorn;
        if (zodiac == "Aquarius")     return Zodiac::Aquarius;
        if (zodiac == "Pisces")       return Zodiac::Pisces;

        throw std::invalid_argument("Unknown zodiac string: " + zodiac);
    }
}
