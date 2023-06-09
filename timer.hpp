#ifndef NMAP_PREV_TIMER_HPP
#define NMAP_PREV_TIMER_HPP
#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <type_traits>
#include <chrono>
#include <string>

struct scope_timer{
    using clock = std::chrono::high_resolution_clock;
    decltype(clock::now()) start_time;
    const std::string name;
    explicit scope_timer(std::string name = "") : name(std::move(name)) {start_time = clock::now();}
    ~scope_timer(){
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - start_time);
        printf("%s Time: %lf seconds\n",name.c_str(),(double)duration.count() / 1000);
    }
};

#endif //NMAP_PREV_TIMER_HPP