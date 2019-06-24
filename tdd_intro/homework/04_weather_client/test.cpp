/*
Weather Client

You are going to develop a program that gets the statistics about weather in the current city
using information from a certain server. The goal is to calculate statistics using the data from weather server.

To communicate with the weather server you have to implement interface IWeatherServer,
which provides the raw string from the real server for the requested day and time.

The real server (i.e. "weather.com") gets the requests in this format:
"<date>;<time>", for example:
"31.08.2018;03:00"

The server answers on requests with string like this:
"20;181;5.1"
This string contains the weather for the requested time and means next:
"<air_temperature_in_celsius>;<wind_direction_in_degrees>:<wind_speed>".
Wind direction value may be in range from 0 to 359 inclusively, temperature may be negative.

The task:
1. Implement fake server, because interacting with real network is inacceptable within the unit tests.
To do this, you need to use real server responses. Fortunately, you've collected some results for the several dates from the weather server.
Each line means "<request>" : "<response>":

"31.08.2018;03:00" : "20;181;5.1"
"31.08.2018;09:00" : "23;204;4.9"
"31.08.2018;15:00" : "33;193;4.3"
"31.08.2018;21:00" : "26;179;4.5"

"01.09.2018;03:00" : "19;176;4.2"
"01.09.2018;09:00" : "22;131;4.1"
"01.09.2018;15:00" : "31;109;4.0"
"01.09.2018;21:00" : "24;127;4.1"

"02.09.2018;03:00" : "21;158;3.8"
"02.09.2018;09:00" : "25;201;3.5"
"02.09.2018;15:00" : "34;258;3.7"
"02.09.2018;21:00" : "27;299;4.0"

IMPORTANT:
* Server returns empty string if request is invalid.
* Real server stores weather only for times 03:00, 09:00, 15:00 and 21:00 for every date. Do not use other hours in a day.

2. Implement IWeatherClient using fake server.
*/

// Test plan
// Parse response from server and get temperature
// 1.Send 1 date/time get response, get temperature 20
// 2. send 2nd dateTime get Temparature 23
// get Wind direction
// 1. 1st request wind 181
// 2. 2nd request wind 204
// get windSpeed
// 1. 3st request wind 4.3
// 2. 4nd request wind 4.5
// getMinTemp/MaxTemp
// 1. Send 4 day times, receive responsec, calculate min
// 2. Send 4 day times, receive responsec, calculate max
// getAverageWindDirection
// 1. Send 4 day times, receive response, calculate averageWind direction
// getAverageWindSpeed
// 1. Send 4 day times, receive response, calculate windSpeed
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <map>

int getTemp(const std::string& request) {
    std::string substr = request.substr(0, request.find(';'));
    int result = std::atoi(substr.c_str());
    return result;
}

int getWindDirection(const std::string& request) {
    std::string substr = request.substr(request.find(';') + 1).substr(0, ';');
    int result = std::atoi(substr.c_str());
    return result;
}

double getWindSpeed(const std::string& request) {
    std::string substr = request.substr(request.find(';') + 1).substr(0, ';');
    substr = substr.substr(substr.find(';') + 1);
    double result = std::atof(substr.c_str());
    return result;
}

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw response with weather for the given day and time in request
    virtual std::string GetWeather(const std::string& request) = 0;
};

class MockWeatherServer : public IWeatherServer{
    std::map<std::string, std::string> serverMap = {{"31.08.2018;03:00", "20;181;5.1"}, {"31.08.2018;09:00", "23;204;4.9"},
                                                    {"31.08.2018;15:00", "33;193;4.3"}, {"31.08.2018;21:00", "26;179;4.5"},
                                                    {"01.09.2018;03:00", "19;176;4.2"}, {"01.09.2018;09:00","22;131;4.1"},
                                                    {"01.09.2018;15:00", "31;109;4.0"}, {"01.09.2018;21:00", "24;127;4.1"},
                                                    {"02.09.2018;03:00", "21;158;3.8"}, {"02.09.2018;09:00", "25;201;3.5"},
                                                    {"02.09.2018;15:00", "34;258;3.7"}, {"02.09.2018;21:00", "27;299;4.0"}};

    std::string GetWeather(const std::string& request) override {
        return serverMap[request];
    }
};

// Implement this interface
class IWeatherClient
{
public:
    virtual ~IWeatherClient() { }
    virtual double GetAverageTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMinimumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetAverageWindDirection(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) = 0;
};

class WeatherClient : public IWeatherClient {

public:
    WeatherClient(IWeatherServer* weatherServer){
        this->weatherServer = weatherServer;
    }

    double GetAverageTemperature(IWeatherServer& server, const std::string& date) {
        return 0;
    }

    double GetMinimumTemperature(IWeatherServer& server, const std::string& date) {
        int resultMin = 0;
        std::vector<int> tempList;
        tempList.push_back(getTemp(server.GetWeather(date+";03:00")));
        tempList.push_back(getTemp(server.GetWeather(date+";09:00")));
        tempList.push_back(getTemp(server.GetWeather(date+";15:00")));
        tempList.push_back(getTemp(server.GetWeather(date+";21:00")));
        auto result = std::min_element(std::begin(tempList), std::end(tempList));
        if (std::end(tempList)!=result)
            resultMin = *result;
        return resultMin;
    }

    double GetMaximumTemperature(IWeatherServer& server, const std::string& date) {
        return 0;
    }
    double GetAverageWindDirection(IWeatherServer& server, const std::string& date) {
        return 0;
    }
    double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) {
        return 0;
    }
    IWeatherServer* weatherServer;
};



TEST(TemparatureParse, getTemparature3h) {
    IWeatherServer* server = new MockWeatherServer();
    ASSERT_EQ(server->GetWeather("31.08.2018;03:00"), "20;181;5.1");
}

TEST(TemparatureParse, getTemparature3hEq20Celsius) {
    IWeatherServer* server = new MockWeatherServer();
    std::string srvResponse = server->GetWeather("31.08.2018;03:00");
    ASSERT_EQ(getTemp(srvResponse), 20);
}

TEST(TemparatureParse, getTemparature9hEq33Celsius) {
    IWeatherServer* server = new MockWeatherServer();
    std::string srvResponse = server->GetWeather("31.08.2018;15:00");
    ASSERT_EQ(getTemp(srvResponse), 33);
}

TEST(WindDirectionParse, getWind3hEq181WindDir) {
    IWeatherServer* server = new MockWeatherServer();
    std::string srvResponse = server->GetWeather("31.08.2018;03:00");
    ASSERT_EQ(getWindDirection(srvResponse), 181);
}

TEST(WindDirectionParse, getWindDate1Time03Eq176WindDir) {
    IWeatherServer* server = new MockWeatherServer();
    std::string srvResponse = server->GetWeather("01.09.2018;03:00");
    ASSERT_EQ(getWindDirection(srvResponse), 176);
}

TEST(WindSpeedParse, getWindSpeedDate1Time03Eq4point2) {
    IWeatherServer* server = new MockWeatherServer();
    std::string srvResponse = server->GetWeather("01.09.2018;03:00");
    ASSERT_EQ(getWindSpeed(srvResponse), 4.2);
}

TEST(WindSpeedParse, getWindSpeedDate31Time03Eq5point1) {
    IWeatherServer* server = new MockWeatherServer();
    std::string srvResponse = server->GetWeather("31.08.2018;15:00");
    ASSERT_EQ(getWindSpeed(srvResponse), 4.3);
}

TEST(CalculateMinMax, getMinTemp31Date) {
    IWeatherServer* server = new MockWeatherServer();
    IWeatherClient* client = new WeatherClient(server);
    ASSERT_EQ(client->GetMinimumTemperature(*server, "31.08.2018"), 20);
}

TEST(CalculateMinMax, getMinTemp01Date) {
    IWeatherServer* server = new MockWeatherServer();
    IWeatherClient* client = new WeatherClient(server);
    ASSERT_EQ(client->GetMinimumTemperature(*server, "01.09.2018"), 19);
}



