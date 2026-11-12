# Setup, compilation, and execution

## 1. Open the project

```sh
cd path/to/posix_threads_git
```

Use the repository root for the commands below. Files live under `src/`, not directly in the root.

## 2. Verify your compiler and SDK (macOS)

```sh
xcode-select -p
xcrun --show-sdk-path
which clang
xcrun --find clang
```

On the original Mac, `which clang` pointed to `/opt/local/libexec/llvm-18/bin/clang`, while Xcode and its macOS SDK were present. That MacPorts compiler reported `fatal error: 'stdio.h' file not found`. `xcrun clang` selects Apple's toolchain and is the recommended build command here. A header-not-found error is a toolchain/SDK configuration issue, not evidence that the pthread logic is wrong.

## 3. Compile one program

```sh
xcrun clang -Wall -Wextra -pthread -O0 src/problem3.c -o problem3
```

- `xcrun clang`: invoke the compiler selected by Xcode.
- `-Wall -Wextra`: request common compiler warnings.
- `-pthread`: compile/link with pthread support.
- `-O0`: disable optimization for these teaching experiments; it **does not** make data races safe or guarantee a particular output.
- `src/problem3.c`: source file.
- `-o problem3`: executable name.

If compilation succeeds, it usually prints nothing. Run it with `./problem3`.

## 4. Compile and run all six

```sh
for n in 1 2 3 4 5 6; do
  xcrun clang -Wall -Wextra -pthread -O0 "src/problem${n}.c" -o "problem${n}" || exit 1
done

for n in 1 2 3 4 5 6; do
  echo "=== Problem $n ==="
  "./problem${n}"
done
```

## 5. Re-run to observe scheduling

```sh
./problem2
./problem2
./problem4
./problem4
./problem5
./problem6
./problem6
```

Different orders in Problems 2 and 4 are normal. Problem 6 may repeatedly print 5000 even though it is racy. Do not modify or invent measured results to make the race appear.

## 6. Save and push to Git

```sh
git init
git add README.md docs src .gitignore
git commit -m "Document POSIX thread exercises 1-6"
```

To push, first create a remote repository on GitHub, then replace `YOUR_USERNAME` and `YOUR_REPOSITORY`:

```sh
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/YOUR_REPOSITORY.git
git push -u origin main
```

If the repository already exists and has a remote, do not reinitialize it or add a duplicate remote; copy the files into that repository and commit normally.
