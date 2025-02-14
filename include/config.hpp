#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace config {
    constexpr auto version = "0.1.0";
    constexpr auto author = "Jacob Brown";
    constexpr char prompt[] = "brsh> ";
    const std::string red("\033[0;36m");
    const std::string reset("\033[0m");
    constexpr char ascii[] = R"(
 __                       __      
[  |                     [  |     
 | |.--.   _ .--.  .--.   | |--.  
 | '/'`\ \[ `/'`\]( (`\]  | .-. | 
 |  \__/ | | |     `'.'.  | | | | 
[__;.__.' [___]   [\__) )[___]|__]
)";
}

#endif 