#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ostream>
#include <sstream>
#include <string>
#include <string_view>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

class OutputDevice {
public:
    virtual ~OutputDevice() = default;

    /**
     * @brief print_line prints the line (somehow)
     * @param message
     */
    virtual void print_line(std::string_view message) = 0;
};

class MockOutputDevice : public OutputDevice {
public:
    MOCK_METHOD(void, print_line, (std::string_view message));

    void record_output()
    {
        ON_CALL(*this, print_line).WillByDefault([this](std::string_view message) {
            recorder << message << "\n";
        });
    }

    std::string recorded_output() const
    {
        return recorder.str();
    }

private:
    std::ostringstream recorder;
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

class Greeter {
public:
    Greeter(OutputDevice* out)
        : out { out }
    {
    }

    void greet(std::string_view whom)
    {
        std::string message { "Hello, " };
        message.append(std::begin(whom), std::end(whom));
        out->print_line(message);
    }

private:
    OutputDevice* out;
};

namespace c {

static const int FOO = 42;
}

namespace a {
namespace b {
    namespace c {
        static const int FOO = 23;
    }

    namespace d {
        static const int BAR = ::c::FOO;
    }
}
}

TEST(GreeterTest, says_hello)
{
    MockOutputDevice out;
    out.record_output();
    EXPECT_CALL(out, print_line("Hello, world"sv));

    Greeter greeter { &out };
    greeter.greet("world");

    EXPECT_EQ("Hello, world\n"s, out.recorded_output());
}
