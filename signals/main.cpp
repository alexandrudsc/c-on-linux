/**
 * App that waits for user input and stops when handling SIGTERM
 */

#include <iostream>
#include <atomic>
#include <cstdio>
#include <csignal>

using namespace std;

atomic_bool run(true);

void handle_sig(int signum)
{
  if (signum == SIGTERM)
  {
    cout << "Signal caught\n";
    run = false;
  }
  else if (signum == SIGINT)
  {
    cout << "\nReally? (y/n) ";
    char a = 'n';
    cin >> a;
    if (a == 'Y' || a == 'y')
    {
      run = false;
    }
  }
}

int main ()
{
  int a;
  // register signal handler
  // use sigaction instead of signal as per man page
  //std::signal(SIGTERM, handle_sig);
  struct sigaction act;
  act.sa_handler = handle_sig;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  sigaction(SIGTERM, &act, nullptr);
  sigaction(SIGINT, &act, nullptr);
  
  while(run)
  {
    cout << "Command: ";
    a = getchar();
    cout << "Char: " << +a << endl;
    if (a == char_traits<char>::eof())
    {
      cout << "EOF on stdin\n";
    }
    cout << "\n";
    if (a == 'X')
    {
      break;
    }
  }
  return 0;
}
