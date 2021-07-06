#include <gtest/gtest.h>

#include <ostream>
#include <sstream>
#include <string_view>

class OutputDevice {
public:
    virtual ~OutputDevice() = default;

    /**
     * @brief print_line prints the line (somehow)
     * @param message
     */
    virtual void print_line(std::string_view message) = 0;
};

class StreamPrinter final : public OutputDevice {
public:
    StreamPrinter(std::ostream& out)
        : out { out }
    {
    }

    void print_line(std::string_view message) override
    {
        out << message << std::endl;
    }

private:
    std::ostream& out;
};

TEST(StreamPrinterTest, prints)
{
    std::ostringstream buffer;
    StreamPrinter sp { buffer };

    sp.print_line("Hello world!");
    EXPECT_EQ(buffer.str(), "Hello world!\n");
}

class InputDevice {
public:
    virtual ~InputDevice() = default;

    virtual std::string read_line() = 0;
};

class Console : public OutputDevice, public InputDevice {
public:
    void print_line(std::string_view message) override
    {
        std::cout << message << std::endl;
    }
};

class ShoutingConsole : public Console {
public:
    void print_line(std::string_view message) override
    {
        std::string upper_case { message.begin(), message.end() };
        std::transform(upper_case.begin(), upper_case.end(), upper_case.begin(), [](char c) {
            return std::toupper(c);
        });

        Console::print_line(upper_case);
    }
};
