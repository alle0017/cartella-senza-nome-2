#include <stdio.h>
#include <stdlib.h>

#define TERMINATOR '\0'


typedef struct List {
      List*next;
      List*prev;
      char elem;
} List;

typedef struct {
      List*input_head;
      List*output_head;
      List*mem_head;
} Turing;

//list utils
// add to the end of the list
List* push_front( char new, List*head );
// add to the start of the list
List* push_back( char new, List*head );
char get_last( List*head );
char get_first( List*head );

// turing machine implementation
Turing* new_turing( char*input_str );
char read_in_left( Turing* machine );
char read_in_right( Turing* machine );
char read_mem_left( Turing* machine );
char read_mem_right( Turing* machine );
Turing* write_mem( Turing* machine, char new );
Turing*override_mem( Turing* machine, char new );
Turing* write_out( Turing* machine, char output );
void print_output( Turing* machine );

//other utils
void add_one( Turing* machine );
int char_to_num( char c );
char num_to_char( int c );

int main( int argc, char*argv[] ){
      if( argc < 2 )
            printf("No arguments passed. program ended");
      
      Turing* machine = new_turing( argv[1] );
      add_one( machine );

      return 0;
}
int char_to_num( char c ){
      return (int)(c - '0');
}
char num_to_char( int num ){
      return (char)(num + '0');
}
List* push_front( char new, List*head ){

      if( !head ){
            head = (List*)malloc( sizeof( List ) );
            head->prev = NULL;
            head->elem = new;
            head->next = NULL;

            return head;
      }
      List* el = head;
      while( el->next ){
            el = el->next;
      }
      el->next = (List*)malloc( sizeof( List ) );
      el->next->prev = el;
      el->next->next = NULL;
      el->next->elem = new;
      
      return head;
}

List* push_back( char new, List*head ){

      if( !head ){
            head = (List*)malloc( sizeof( List ) );
            head->prev = NULL;
            head->elem = new;
            head->next = NULL;

            return head;
      }
      List* el = head;
      while( el->prev ){
            el = el->prev;
      }
      el->prev = (List*)malloc( sizeof( List ) );
      el->prev->next = el;
      el->prev->prev = NULL;
      el->prev->elem = new;

      return head;
}
char get_last( List*head ){
      List* el = head;
      if( !el ){
            return '0';
      }
      while( el->next ){
            el = el->next;
      }
      return el->elem;
}
char get_first( List*head ){
      List* el = head;
      if( !el ){
            return '0';
      }
      while( el->prev ){
            el = el->prev;
      }
      return el->elem;
}
Turing* new_turing( char*input_str ){
      Turing* machine = (Turing*) malloc(sizeof(Turing));
      int i = 0;

      machine->input_head = NULL;
      machine->output_head = NULL;
      machine->mem_head = NULL;
      while( input_str[i] != '\0' ){
            machine->input_head = push_front( input_str[i], machine->input_head );
            i++;
      }
} 
char read_in_left( Turing* machine ){
      if( machine->input_head->prev ){
            machine->input_head = machine->input_head->prev;
            return machine->input_head->elem;
      }
      return TERMINATOR;
}
char read_in_right( Turing* machine ){
      if( machine->input_head->next ){
            machine->input_head = machine->input_head->next;
            return machine->input_head->elem;
      }
      return TERMINATOR;
}
char read_mem_left( Turing* machine ){
      if( machine->mem_head->prev ){
            machine->mem_head = machine->mem_head->prev;
            return machine->mem_head->elem;
      }
      return TERMINATOR;
}
char read_mem_right( Turing* machine ){
      if( machine->mem_head->next ){
            machine->mem_head = machine->mem_head->next;
            return machine->mem_head->elem;
      }
      return TERMINATOR;
}
Turing* write_mem( Turing* machine, char new ){
      if( machine->mem_head && machine->mem_head->next ){
            List*tmp = machine->mem_head->next;
            machine->mem_head->next = (List*)malloc(sizeof(List));
            machine->mem_head->next->next = tmp;
            tmp->prev = machine->mem_head->next;
            machine->mem_head->next->elem = new;
            return machine;
      }
      push_front( new, machine->mem_head );
      return machine;
}
Turing*override_mem( Turing* machine, char new ){
      if( machine->mem_head ){
            machine->mem_head->elem = new;
            return machine;
      }
      push_front( new, machine->mem_head );
      return machine;
}
Turing* write_out( Turing* machine, char output ){
      push_front( output, machine->output_head );
}
void print_output( Turing* machine ){
      List*el = machine->output_head;

      while( el->prev ){
            el = el->prev;
      }
      while( el ){
            printf( "%c", el->elem );
            el = el->next;
      }
}

void add_one( Turing* machine ){

      while( read_in_right( machine ) != TERMINATOR ){}

      while( read_in_left( machine ) == '9' ){
            write_out( machine, '0' );
      }
      write_out( 
            machine, 
            num_to_char( 
            char_to_num( 
            read_in_left( machine ) 
            ) + 1 
      ) );
      char next = read_in_left( machine );
      while( next != TERMINATOR ){
            write_out( machine, next );
            next = read_in_left( machine );
      }
      print_output( machine );
}
