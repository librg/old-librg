# librg coding style

(and other stuff)

## Naming convention

0. All files should have lowercased name
1. Use lowercase for variables, structs, method/function names, namespaces
2. If name of any item from list above consists of 2 or more words, use `_` to distinguish them. (snake_case)
3. Structs and other type representations should have `_t` postfix after actual name
4. Classes should have camel cased name with leading capital letter (PascalCase) `ExampleName`

## Brackets, braces, parens

1. Each namespace definition should have `{` on the next line
2. Each function/method definition should have `{` on the next line
3. Each for/if/while/etc contruction should have `{` on the same line
4. Each for/if/while/etc contruction should have `(` with space after (`if (a == 15`)
5. Each for/if/while/etc contruction should have `{}` except its single-lined (on same line with if/... used only with `return` or exception throws)
6. Each `catch` after `try` contruction should be on the next line after closing try `}` brace

## Operators

1. Each opreator should be surrounded by 1 space from both sides `int a = 5;`, except small inline math equations
2. If its possible, you should try to make operators lined up with ones defined on nearby lines:

```cpp
int somevar = 15;
float asd   = 124.0f;
bool hello  = false;
```

## Includes

1. All includes should have `<>` brackets, except ones that are for local files (near current file).

## Code and Library

0. Each header file should have include-guard with `#ifndef filename_h` and closing `#endif // filename_h`
1. Each included header from library should be located in file its supposed to be used
2. If library uses namepsaces, you should not use `using namepsace somelib;`
3. Keyword `auto` should be used in most of the cases, in local functions/methods
4. Long repeating types should be defined via `using` or `typedef` (first one is much more preferable)
5. All private (or intended to be private) members should have single underscore symbol `_`

## Comments

1. All public methods and variables should have multiline jsdoc-like comments
2. Methods should have inline comments in places, where they can give a good description for what is happening or can improve readability
3. You are recommended to put comment with copyright notice in the beginning of the each file
