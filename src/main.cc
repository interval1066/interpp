#include <iostream>
#include <cstdlib>
#include "main.h"

// Create properties object
// Deserialize properties and load them into the object
// Process command line opts
// execute command loop

/**
 * Anticipate ctrl + c
 *
 * no signals we need to handle as far as we
 * know right now. May change in the future.
 */
void
sig_handler(int sign)
{
    signal(SIGINT, sig_handler);
}

/**
 * initial state
 *
 * set defaults including prompt which is a "> " (greater than + space), can be changed
 * via the 'prompt' intrinsic command.
 */
static int
init(void)
{
}

static int
readconfig(void)
{
    user.admin = 0;
    char adminperm[10] = { 0 };
    char cfg_path[MAXBUF] = { 0 };

    get_userdir(cfg_path);
#ifndef _MSC_VER
    strcat(cfg_path, "/.interp.ini");
#else
    strcat(cfg_path, "\\.interp.ini");
#endif
    ini_table_s* config = ini_table_create();
    if(ini_table_read_from_file(config, cfg_path)) {

        strcpy(user.prompt, ini_table_get_entry(config, "Main", "prompt"));
        user.loglevel = atoi(ini_table_get_entry(config, "Main", "loglevel"));
        strcpy(adminperm, ini_table_get_entry(config, "Main", "admin"));

        if(strcmp(adminperm, "true") == 0)
            user.admin = 1;
    }
    ini_table_destroy(config);

    return CMD_OK;
}

static int
writeconfig(void)
{
    char cfg_path[MAXBUF] = { 0 };
    char astr[10] = { 0 };
    get_userdir(cfg_path);

#ifndef _MSC_VER
    strcat(cfg_path, "/.interp.ini");
#else
    strcat(cfg_path, "\\.interp.ini");
#endif

    ini_table_s* config = ini_table_create();
    if(ini_table_read_from_file(config, cfg_path)) {

        ini_table_create_entry(config, "Main", "prompt", user.prompt);
        myitoa(user.loglevel, astr);
        ini_table_create_entry(config, "Main", "loglevel", astr);

        if(user.admin == 1)
            ini_table_create_entry(config, "Main", "admin", "true");
        else
            ini_table_create_entry(config, "Main", "admin", "false");

        ini_table_write_to_file(config, cfg_path);
    }

    ini_table_destroy(config);

    return CMD_OK;
}

int
main(int argc, char** argv)
{
	size_t size, len;
	bool bDo = true;
	std::string cmd_string;

	init();
	readconfig();

	do {
		len = 0;
		std::string cmd_string;
		cout << "%s " << user.prompt);

		getline(std::cin, cmd_string);

		// ???? Just copying and pasting for now, this will undergo many changes...
		size = cmd_string.length();
		// this needs special care, I know there's an object oriented way to do this,
		// suspect this will be completly different soon
		char** splitresult = split(cmd_string, ' ', &size);
		bDo = proc_cmds(splitresult, size);

		free(&splitresult[0]);
	} while (bDo);

	writeconfig();

	return EXIT_SUCCESS;
}
