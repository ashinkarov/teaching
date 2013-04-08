# encoding: utf-8

slide <<-EOS, :center
    Feedback session for assignment-01

 

    Artem Shinkarov
  
    07 Feb 2013
EOS

slide <<-EOS, :code
    Plan for today:

        * Makefiles
        * Argument handling in C
        * Memory allocation in C
        * System calls
        * Forks and pipes
        * Error handling
EOS


section "Introduction to Makefiles" do 
    slide <<-EOS, :code
        Makefiles are useful for automating *compilation* process.

            1. It tracks dependencies.
            2. Rich syntax for conditional compilation.
            3. Loads of things are pre-defined.
    EOS

    slide <<-EOS, :code
        Makefiles general concepts

            1. Macro-variables
            2. Target rules
            3. Dependencies
    EOS
  
    slide <<-EOS, :code
        Macro-variables in Makefiles

            VAR := value

            all:
                    echo $(VAR)

      
        Values are text-based, $(VAR) -- get value of VAR.
    EOS
 
    slide <<-EOS, :code
        Target rules in Makefiles (1)

            all: prog1 prog2
      
            prog1: prog1.c
                    $(CC) -o prog1 prog1.c

            prog2: prog2.c
                    $(CC) -o prog2 prog2.c
  
        Note the *tab* in the target recipe
        By default entry target is called "all"
    EOS

    slide <<-EOS, :code
        Target rules in Makefiles (2)
    
            CFLAGS := -Wall -Wextra -pedantic -std=c99

            all: prog1 prog2
            prog%: prog%.o

            clean:
                $(RM) prog1 prog2 *.o
    EOS

    slide <<-EOS, :code
        Dependencies in Makefiles (2)
    
            all: prog1 prog2
            prog%: prog%.o
      
            prog1.o: inc1.h inc2.h
            prog2.o: inc3.h
  
      
        More info: http://www.gnu.org/software/make/manual
    EOS
end

section "Argument handling in C" do 
    slide <<-EOS, :code
        Any C program must have an entry point called "main".
    
        Main function can have the following signatures:
            
            int main ();
            int main (int argc, char *argv[]);
            int main (int argc, char *argv[], char *envp[]);
    
        argc -- number of arguments, 0-th argument -- the binary
        argv -- array of arguments of size argc+1
        envp -- array of VAR=VAL environment
    EOS


    slide <<-EOS, :center
        How can we print all the arguments that were
        passed to the program?

        Demo
    EOS

    slide <<-EOS, :code
        There are three different execv calls:
            
            execv (char * path, char *arg[]);
            execvp (char * file, char *arg[]);
            execvpe (char * file, char *arg[], char *envp[]);

        What is the difference?
    EOS

    slide <<-EOS, :center
        How to duplicate arguments from argv to
        arg, in order to call execv(p|pe)?
        function?
    EOS
end

## Memory allocation section

section "Memory allocation in C" do
    slide <<-EOS, :code
        Memory management in C is explicit!

            ...
            char a[10];
            char b[] = "hello";
            char *c = "xyz";
            char *d;
            ...
    
        What is the difference?
    EOS

    slide <<-EOS, :code
        Dynamic memory allocation

            char * c;

            c = malloc (sizeof (char) * 10);
            ...
            free (c);

        Things to avoid:
      
            * using 'c' before malloc
            * using 'c' after free
            * using free on 'c' more than once
    EOS

    slide <<-EOS, :center
        How do we declare an array which would be able
        to accommodate 25 file-names?
        
        Demo
    EOS
end


section "System calls" do
    slide <<-EOS, :center
        System calls are tircky!

        Read man pages *carefully*

        Consider the following code
    EOS
    
    slide <<-EOS, :code
        int main() {
            int fd = open("/tmp/pattern.example",
                          O_CREAT | O_TRUNC | O_RDWR,
                          S_IRUSR | S_IWUSR);
            if (fd == -1)
                return EXIT_FAILURE;

            const char *data = "Some text that you want to write.";
            write(fd, data, strlen(data));
            close(fd);

            return 0;
        } 
    EOS

    slide <<-EOS, :code
        Manual says:
            "write() writes up to count bytes from the buffer..."

        Anything suspicious?

        Well, what would be the right code then?
    EOS

    slide <<-EOS, :code
        int written = 0;
        int n;
        while (written < strlen(data)) {
            if ((n = write(fd, data + written, strlen(data) - written)) < 0) {
                /* Handle error.  */
            }

            written += n;
        } 
    EOS
end



section "Pipes and forks (demo)" do
end


section "Error handling in C" do
    slide <<-EOS, :code
        If anything bad can happen, it probably will
                
                                      --Murphy's law

        Always try to catch potentially dangerous
        piees of code.
    EOS

    slide <<-EOS, :code
        In C there are the following common mechanisms

            1. ERRNO based functions: perror, strerror, etc.
            2. Functionality from <err.h>
            3. Assertions.
            4. Custom print/return.
    EOS
    
    slide <<-EOS, :center
        Demo
    EOS
end


section "That's all, thanks!" do
end

