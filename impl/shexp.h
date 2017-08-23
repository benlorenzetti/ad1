#ifndef SHEXP_H
#define SHEXP_H

#include "string.h" // uses ustr type and ustr procedures
#include "array.h"  // uses sorted array for global operators table

union symbol;
struct identifier;
struct operator;
struct namespace;

union shexp;
struct atom;
struct xcell;


/*  
    Lexically, there are three genera of symbols in Ad1:

        1) identifiers,
        2) operators, and
        3) namespaces.

        Identifiers name uniquely some entity, which may be abstract
    or concrete, i.e. which may exist as an object in memory primarily
    at  compile time or runtime. Identifiers have 1) a name string,
    which must be either unique or NULL (an anonymous entity),
    2) a type tree describing themselves, and 3) a value pointer for
    abstract values.
        An important property of the identifier object type is not
    apparent from its structure. Named identifiers not only must have 
    a unique name string, but all identifiers must maintain a stable
    address in memory for their entire referencable lifetime during
    compilation. Data structures containing identifiers for lookup
    must preserve this invariant.

        Operators are like verbs in English and indicate some action
    being applied to their arguements, again abstractly or concretely;
    at compile time or at runtime. Operators are ultimately backed by 
    procedures. Unlike identifiers, operators may be overloaded so
    that multiple procedures with different type signatures may share
    the same name. Operators have 1) a name string, 2) a type tree
    that makes them unique, 3) a pointer to an AST or an identifier
    containing a compiled instruction sequence, and 4) two integral
    values indicating their precedence in the AST relative to
    operators on their left and right in text.
        Operator symbols are maintained in a weak, total order
    alphabetically by the compiler for lexical lookup.

        Finally, statically scoped namespaces are added to the concept
    of identifiers to facilitate name reuse in different contexts/
    parts of the program. Namespace objects share memory shape with
    identifiers and logically create a heirarchial tree of names like
    how a computer filesystem is organized. Like identifiers,
    namespaces within the tree must be unique compared to all their
    immediate siblings and must maintain stable addresses in
    compiler data structures.
    
*/

union symbol {
    struct identifier id;
    struct operator op;
    struct namespace namespace;
    ustr name;
};

struct identifier {
    ustr name;
    Nint type;
    Nint adstract_value;
};

struct namespace {
    ustr name;
    Nint next_sibling_rel;
    Nint parent_rel;
};

struct operator {
    ustr name;
    Nint type;
    Nint adstract_value;
    int l2r_precedence;
    int r2l_precedence;
};

#endif
