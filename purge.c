#include <stdio.h>
#include <stdlib.h>

static const char app_banner[] =
    "    ____                      \n"
    "   / __ \\__  ___________ ____\n"
    "  / /_/ / / / / ___/ __ `/ _ \\\n"
    " / ____/ /_/ / /  / /_/ /  __/\n"
    "/_/    \\__,_/_/   \\__, /\\___/\n"
    "                 /____/\n";

void ask_and_run(const char *question, const char *command) {
    char choice;

    printf("%s [Y/n]: ", question);
    choice = getchar();

    if (choice != '\n')
        while ((getchar()) != '\n');

    if (choice == 'n' || choice == 'N') {
        printf("Skipping...\n\n");
    }
    else {
        printf("Performing %s...\n\n", command);
        system(command);
        printf("\n");
    }
}

int main() {

    char built_command[18];
    int n_flag;
    char choice;

    printf("%s", app_banner);
    ask_and_run("\nRemove Obsolete Distfiles?", "eclean-dist");
    ask_and_run("Remove Obsolete Binary Packages?", "eclean-pkg");

    printf("Remove Obsolete Dependencies? [Y/n]: ");
    choice = getchar();

    if (choice != '\n')
        while ((getchar()) != '\n');

    if (choice == 'n' || choice == 'N') {
        printf("Skipping...\n\n");
    }
    else {
        ask_and_run("\nRun Full System Upgrade To Ensure Purge Removes Only Dependencies That Are Truly Obsolete? (NOT RECOMMENDED FOR NON DIST-KERNELS MIGHT REQUIRE MANUAL CONFIGURATION IF YOU ARE USING A NON DIST KERNEL AND WANT TO MAKE SURE OF THIS PLEASE QUIT AND UPDATE FOR YOUR CONFIGURATION)", "emerge --ask --verbose --update --newuse --deep @world");
        printf("Performing emerge --ask --depclean\n\n");
        system("emerge --ask --depclean");
    }

    ask_and_run("List Current Installed Kernel Binaries For Removal Of Obsolete Ones?", "eclean-kernel -l");

    printf("Remove Obsolete Kernels? [Y/n]: ");
    choice = getchar();

    if (choice != '\n')
        while ((getchar()) != '\n');

    if (choice == 'n' || choice == 'N') {
        printf("Skipping...\n\n");
    }
    else {
        printf("What Value To Pass To The -n Flag For eclean-kernel: ");

        while (scanf("%d", &n_flag) != 1) {
            printf("Enter a Valid Number: ");
            while (getchar() != '\n');
        }

        snprintf(built_command, sizeof(built_command), "eclean-kernel -n%d", n_flag);
        printf("Performing %s\n\n", built_command);
        system(built_command);
    }

    return 0;
}
