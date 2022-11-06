#include "cipher.h"
#include "tests.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CIPHER_MODE_ARGC 5
#define TEST_MODE_ARGC 2
#define K_CONVERSION_BASE 10
#define ALPHABET_LEN 26
#define MAX_CHAR_IN_LINE 1024
#define VALID_TEST_COMMAND "test"
#define VALID_ENCODE_COMMAND "encode"
#define VALID_DECODE_COMMAND "decode"
#define INVALID_TEST_COM_OUTPUT "Usage: cipher test\n"
#define INVALID_K_OUTPUT "The given shift value is invalid.\n"
#define INVALID_CIPHER_COM_OUTPUT "The given command is invalid.\n"
#define INVALID_PATH_OUTPUT "The given file is invalid.\n"
#define INVALID_ARG_NUM "The program receives 1 or 4 arguments only.\n"

/**
 * Checks if the given command is valid. if so, calls to run_tests()
 * @param argv: given user input array.
 * @return true if it is valid test command and all
 * tests passed, false otherwise.
 */
bool test_mode(const char *argv[]);

/**
 * Cipher mode management function.
 * @param argv: given user input array.
 * @return true if all arguments are valid and cipher process
 * went well, false otherwise.
 */
bool cipher_mode(const char *argv[]);

/**
 * Runs all tests required.
 * @return true if all tests passed, false otherwise.
 */
bool run_tests();

/**
 * Checks if the k given by the user is valid.
 * @param k_string: string for k from user input args.
 * @return true if the given k is valid, false otherwise.
 */
bool k_validation(const char k_string[]);

/**
 * Checks if the given cipher command is valid.
 * @param com_string: the given command by the user.
 * @return true if it is valid cipher command, false otherwise.
 */
bool command_validation(const char com_string[]);

/**
 * Checks if the given file paths are valid and its file exist.
 * @param in_file_path: the given path to the source file by the user.
 * @param out_file_path: the given path to the output file by the user.
 * @return true if it is valid path and files aren't
 * corrupted, false otherwise.
 */
bool files_validation(const char in_file_path[],
                      const char out_file_path[]);

/**
 * Manages the actual encode/decode requested by the user.
 * @param com_string: the given command by the user.
 * @param k: the given number of displacements by the user.
 * @param in_file_path: the given path to the source file by the user.
 * @param out_file_path: the given path to the output file by the user.
 */
void encode_decode_management(const char com_string[],
                              int k, const char in_file_path[],
                              const char out_file_path[]);


bool run_tests()
{
    int tests_sum = test_encode_non_cyclic_lower_case_positive_k()
            + test_encode_cyclic_lower_case_special_char_positive_k()
            + test_encode_non_cyclic_lower_case_special_char_negative_k()
            + test_encode_cyclic_lower_case_negative_k()
            + test_encode_cyclic_upper_case_positive_k()
            + test_decode_non_cyclic_lower_case_positive_k()
            + test_decode_cyclic_lower_case_special_char_positive_k()
            + test_decode_non_cyclic_lower_case_special_char_negative_k()
            + test_decode_cyclic_lower_case_negative_k()
            + test_decode_cyclic_upper_case_positive_k();
    if (tests_sum > 0)
    {
        return false;
    }
    return true;
}

bool test_mode(const char *argv[])
{
    if (strcmp(argv[1], VALID_TEST_COMMAND) != 0)
    {
        fprintf(stderr, INVALID_TEST_COM_OUTPUT);
        return false;
    }
    return run_tests();
}

bool k_validation(const char k_string[])
{
    if ((k_string[0] < '0' || k_string[0] > '9') && k_string[0] != '-')
    {
        fprintf(stderr, INVALID_K_OUTPUT);
        return false;
    }
    for (int i = 1; k_string[i] != '\0'; i++)
    {
        if (k_string[i] < '0' || k_string[i] > '9')
        {
            fprintf(stderr, INVALID_K_OUTPUT);
            return false;
        }
    }
    return true;
}

bool command_validation(const char com_string[])
{
    if (strcmp(com_string, VALID_ENCODE_COMMAND)!= 0
    && strcmp(com_string, VALID_DECODE_COMMAND) != 0)
    {
        fprintf(stderr, INVALID_CIPHER_COM_OUTPUT);
        return false;
    }
    return true;
}

bool files_validation(const char in_file_path[],
                      const char out_file_path[])
{
    FILE *in_file = fopen(in_file_path, "r");
    if (!in_file)
    {
        fprintf(stderr, INVALID_PATH_OUTPUT);
        return false;
    }
    FILE *out_file = fopen(out_file_path, "w");
    if (!out_file)
    {
        fclose(in_file);
        fprintf(stderr, INVALID_PATH_OUTPUT);
        return false;
    }
    return true;
}

void encode_decode_management(const char com_string[],
                              int k, const char in_file_path[],
                              const char out_file_path[])
{
    FILE *in_file = fopen(in_file_path, "r");
    FILE *out_file = fopen(out_file_path, "w");
    char buffer[MAX_CHAR_IN_LINE];
    while (fgets(buffer, MAX_CHAR_IN_LINE, in_file))
    {
        if (strcmp(com_string, VALID_ENCODE_COMMAND) == 0)
        {
            encode(buffer, k);
        }
        if (strcmp(com_string, VALID_DECODE_COMMAND) == 0)
        {
            decode(buffer, k);
        }
        fputs(buffer, out_file);
    }
    fclose(in_file);
    fclose(out_file);
}

bool cipher_mode(const char *argv[])
{
    if (!command_validation(argv[1]))
    {
        return false;
    }
    if (!k_validation(argv[2]))
    {
        return false;
    }
    if (!files_validation(argv[3], argv[4]))
    {
        return false;
    }
    long raw_k = strtol(argv[2], NULL, K_CONVERSION_BASE);
    int final_k = (int) (raw_k % ALPHABET_LEN
            + ALPHABET_LEN) % ALPHABET_LEN;
    encode_decode_management(argv[1], final_k, argv[3], argv[4]);
    return true;
}

int main (int argc, char *argv[])
{
  if (argc == CIPHER_MODE_ARGC)
  {
      if (!cipher_mode((const char **) argv))
      {
          return EXIT_FAILURE;
      }
      return EXIT_SUCCESS;
  }
  if (argc == TEST_MODE_ARGC)
  {
      if (!test_mode((const char **) argv))
      {
          return EXIT_FAILURE;
      }
      return EXIT_SUCCESS;
  }
  fprintf(stderr, INVALID_ARG_NUM);
  return EXIT_FAILURE;
}
