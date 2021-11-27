//
// Created by ma422 on 11/27/2021.
//

#ifndef TUTORLOGGING_DEBUGMODE_HPP
#define TUTORLOGGING_DEBUGMODE_HPP

//Quick Logging
#define DEBUG 0

#if DEBUG == 1
#define LOG(X) std::cout << X << std::endl
#define SPACER() std::cout << std::endl
#elif DEBUG == 0
#define LOG(X)
#define SPACER()
#endif

#endif //TUTORLOGGING_DEBUGMODE_HPP
