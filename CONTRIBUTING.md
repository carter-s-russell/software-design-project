# Contributing to software-design-project

## Code Style Guide

To maintain a consistent and readable codebase, use the following style rules.

### Capitalization (Naming Conventions)

* **`PascalCase`**: Use for `structs`, `enums`, and `classes`.
    * *Example:* `class UserSession;`, `struct UserData;`
* **`camelCase`**: Use for `variables` and `functions`.
    * *Example:* `int userAge;`, `void getUserName();`
* **`SCREAMING_SNAKE_CASE`**: Use for `constants` and `macros`.
    * *Example:* `const int MAX_USERS = 10;`

### Commenting

Use [DoxyGen](https://www.doxygen.nl/) for all in-code documentation. 

* **File Headers:** Every file must begin with a DoxyGen comment block describing its purpose, author, and date.
    ```cpp
    /**
     * @file
     * @brief A brief description of what this file contains.
     * @author [Your Name]
     * @date [Date]
     */
    ```
* **Code Elements:** All `classes`, `structs`, `enums`, `constructors`, `functions`, and public members must have a DoxyGen comment block explaining what they do, their parameters, and what they return.
    ```cpp
    /**
     * @brief Calculates the sum of two integers.
     * @param a The first integer.
     * @param b The second integer.
     * @return The sum of a and b.
     */
    int add(int a, int b);

 ## Commit Message Guidelines

Follow the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) standard. 

Your commit message header should follow this format:
`<type>(<scope>): <subject>`

* **Type:** `feat` (new feature), `fix` (bug fix), `docs` (documentation), `style` (formatting), `refactor`, `test`, `chore` (build/tool changes).
* **Scope (optional):** The module or part of the code affected (e.g., `auth`, `parser`).
* **Subject:** A short, imperative-tense description (e.g., "add login button" not "added login button").

**Good Examples:**
* `feat(auth): add password reset endpoint`
* `fix(parser): correct handling of empty strings`
* `docs(contributing): add DoxyGen examples`

**Bad Examples:**
* `fixed a bug`
* `updated code`
* `stuff`   ```
