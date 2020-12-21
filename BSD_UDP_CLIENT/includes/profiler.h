//
// Created by Григорий Воронов on 25.11.2020.
//

#ifndef PROFILER_H
#define PROFILER_H
#include<chrono>
#include <iostream>
#include <string>

class LogDuration{
public:
	explicit LogDuration(const std::string& mes = "")
	:message(mes + ": "), start(std::chrono::steady_clock::now()) { }
	
	~LogDuration() {
		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout << message << duration << " ms.\n";
	}
private:
	std::string message;
	std::chrono::steady_clock::time_point start;
};
#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) \
  LogDuration UNIQ_ID(__LINE__){message};

#endif
