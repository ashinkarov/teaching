# encoding: utf-8

slide <<-EOS, :center
    Feedback session for assignment-02/03

 

    Artem Shinkarov
  
    19 Mar 2013
EOS

slide <<-EOS, :code
    Plan for today:

        * Argument handling in C (again)
        * Fork tricks/bombs
        * Pointer arithmetic/indexing
        * Memory allocator
EOS


section "Argument handling in C (again)" do 
    slide <<-EOS, :code
        Arguments are unified across exec system calls
            
            execv (char * path, char *arg[]);
            execvp (char * file, char *arg[]);
            execvpe (char * file, char *arg[], char *envp[]);

    EOS

    slide <<-EOS, :code
        What are the arguments?
            
            * Array of strings of unknown length
            * The last element is NULL
            * The first element is a binary/process

    EOS
    
    slide <<-EOS, :code
        Main function signatures
            
            int main ();
            int main (int argc, char *argv[]);
            int main (int argc, char *argv[], char *env[]);
    EOS

    slide <<-EOS, :code
        Getopt library to handle options
            
            * Standard abstraction layer
            * Clean interface
            * Unix standard (+/-)
    EOS
    
    slide <<-EOS, :center
        Demo
    EOS


end

section "Fork tricks/bombs" do 
    slide <<-EOS, :code
        What happens in the following code:

        ...
        int pipefd[2];
        pid = fork ();
        pipe (pipefd);
        if (pid == 0)
            ...
    EOS


    slide <<-EOS, :code
        What happens if:

            #include <stdlib.h>
            #include <unistd.h>

            int main()
            {
                while(1)
                    fork();
            } 
        EOS

    slide <<-EOS, :code
        Or in terms of bash:
             
             :(){ :|:& };:
    EOS
                  
    slide <<-EOS, :code
        How to avoid fork bombs?
            
            * kill -STOP -2
            * kill -CONT pid
            * kill stupid users
    EOS
end

section "Pointer arithmetic" do
    slide <<-EOS, :center
        We are going to use examples from
        http://c-faq.com/
        
        (really nice resource)
    EOS

    slide <<-EOS, :center
        (Q1) What are pointers really good for, anyway? 
    EOS
    slide <<-EOS, :code
        * dynamically-allocated arrays
        * generic access to several similar variables
        * (simulated) by-reference function parameters
        * malloc'ed data structures of all kinds,
          especially trees and linked lists
        * walking over arrays (for example, while parsing strings)
        * efficient, by-reference ``copies'' of arrays and structures
    EOS


    slide <<-EOS, :code
        (Q2) I'm trying to declare a pointer and allocate 
             some space for it, but it's not working. What's 
             wrong with this code?

            char *p;
            *p = malloc(10);
    EOS
    slide <<-EOS, :code
        The pointer you declared is p, not *p.
        p = malloc(10);
    
        It's when you're manipulating the pointed-to memory 
        that you use * as an indirection operator:
        *p = 'H';
    EOS

    slide <<-EOS, :center
        (Q3) Does *p++ increment p, or what it points to? 
    EOS
    slide <<-EOS, :code
        The postfix ++ and -- operators essentially have 
        higher precedence than the prefix unary operators.
        Therefore, *p++ is equivalent to *(p++); 
    EOS

    slide <<-EOS, :code
        (Q4) I have a function which accepts, and is supposed 
        to initialize, a pointer:
        
            void f(int *ip) {
                static int dummy = 5;
                ip = &dummy;
            }

        But when I call it like this: 
            int *ip; f(ip);
        
        the pointer in the caller remains unchanged. 
    EOS
    slide <<-EOS, :code
        To fix it either:
            void f (int **ipp) {
                return *ipp = &dummy;
            }
        Or return the thing:
            int * f () {
                return &dummy;
            }
    EOS

    slide <<-EOS, :code
        Questions with no answers (Q5):
        
        int array[5], i, *ip;
        for(i = 0; i < 5; i++) array[i] = i;
        ip = array;
        printf("%d", *(ip + 3 * sizeof(int)));

    EOS

    slide <<-EOS, :code
        Questions with no answers (Q6):
    
        Why can't I perform arithmetic 
        on a void * pointer? 
    EOS
    
    slide <<-EOS, :center
       Demo
    EOS
end


section "Memory allocator" do
    slide <<-EOS, :code
        0) General principle
        1) Interfaces
        2) So, 'sbrk' or 'mmap'?
        3) Simple list (linked list)
        4) Splitting 
    EOS

    slide <<-EOS, :code
        * Allocates _at least_ N bytes
        * Malloc returns a pointer to an allocated space
        * Further mallocs will NOT allocate this 
          space or any portion of it.
        * Should come with _free_!
    EOS

    slide <<-EOS, :code
        Interfaces
            * malloc
            * free
            * realloc
            * calloc
    EOS

    slide <<-EOS, :center
        What is the difference between 'mmap'
        and 'sbrk'?  Where is the magic?
    EOS

    slide <<-EOS, :code
        Linked list:
            struct chunk {
                size_t sz;
                int on;
                char data[];  /* trick */
            }
    EOS

    slide <<-EOS, :code
        Next chunk:
            void *start, *end, *last;

            struct chunk *ptr = start;
            while (ptr != end) {
                /* do something */
                ptr = (char *)ptr + ptr->sz 
                      + sizeof (struct chunk);
            }
    EOS

    slide <<-EOS, :code
        Splitting
            void split_chunk (struct chunk *c, size_t s);

        Problems and dangers?
    EOS
end

section "That's all, thanks!" do
end

__END__


