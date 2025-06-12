#include <stdio.h>

#ifdef _WIN32
    // Windows includes
    #include <windows.h>
    #include <conio.h>
#else
    // Linux/Unix includes
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/select.h>
#endif

#ifdef _WIN32
    // Windows implementation
    void enable_continuous_mode(void) {
        // Windows doesn't need special setup for _kbhit()
    }
    
    void disable_continuous_mode(void) {
        // Nothing to restore on Windows
    }
    
    int get_key_nonblocking(void) {
        if (_kbhit()) {
            return _getch();
        }
        return 0; // No key pressed
    }
    
    void game_sleep(int milliseconds) {
        Sleep(milliseconds);
    }
    
    void clear_screen(void) {
        system("cls");
    }

#else
    // Linux/Unix implementation
    static struct termios old_termios;
    static int terminal_modified = 0;
    
    void enable_continuous_mode(void) {
        struct termios new_termios;
        
        // Get current terminal settings
        tcgetattr(STDIN_FILENO, &old_termios);
        new_termios = old_termios;
        
        // Disable canonical mode and echo
        new_termios.c_lflag &= ~(ICANON | ECHO);
        new_termios.c_cc[VMIN] = 0;  // Non-blocking read
        new_termios.c_cc[VTIME] = 0; // No timeout
        
        // Apply new settings
        tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
        
        // Make stdin non-blocking
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
        
        terminal_modified = 1;
    }
    
    void disable_continuous_mode(void) {
        if (terminal_modified) {
            tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
            terminal_modified = 0;
        }
    }
    
    int get_key_nonblocking(void) {
        char c;
        if (read(STDIN_FILENO, &c, 1) == 1) {
            return c;
        }
        return 0; // No key pressed
    }
    
    void game_sleep(int milliseconds) {
        usleep(milliseconds * 1000); // usleep takes microseconds
    }
    
    void clear_screen(void) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
#endif