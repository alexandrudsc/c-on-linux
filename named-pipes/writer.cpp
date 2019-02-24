// 
// Writer program to a named pipe 
//
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <string.h>
using namespace std;

/*
 * Writer class. Opens, closes and writes to a pipe
 */
class writer
{
public:
  writer(const ::std::string& pipe_name):name(pipe_name)
  {
    /* create the FIFO (named pipe) */
    mkfifo(name.c_str(), 0666);
    fd = open(name.c_str(), O_WRONLY);
    if (fd == -1)
    {
      throw "Failed to open pipe";
    }
  }
  int write(const ::std::string& msg)
  {
    return ::write(fd, msg.c_str(), msg.size());
  }

  ~writer()
  {
    close(fd);
    unlink(name.c_str());
  }

private:
  int fd = -1;
  const ::std::string& name;
};

/*
 * Write a string 300 times
 */
int main()
{
    ::std::string fifo = "/tmp/fifopipe";
    sleep(2);
    writer w(fifo);
    /* write message to the FIFO */
    std::string msg="This is the string to be reversed\n";
    int i = 300;
    while(--i)
    {
      if (w.write(msg) == -1)
      {
        ::std::cout << "Failed to write: " << msg << ::std::endl;
      }
    }
    return 0;
}
