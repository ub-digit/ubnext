#!/bin/bash

#declare variables commands as a list, environments as a list
commands=("export" "import")
sub_commands=("files" "db")
environments=("lab" "staging" "production")

# declare variables for the connection strings
lab="apps@docker-gu-lab.ub.gu.se"
staging="apps@docker-gu-staging.ub.gu.se"
production="nomad-client-3.ub.gu.se"

environment=$1
command=$2

# Functions
function export_db {
    echo "Downloading database..."
    ssh $connection "cd /apps/ubnext && ./dump-database.sh > /apps/ubnext/database.sql"
    scp $connection:/apps/ubnext/database.sql database.sql
    ssh $connection "rm /apps/ubnext/database.sql"
}

function export_files {
    echo "Downloading files..."
    #check if the directory files exists locally
    if [ -d files ]; then
        mv files files_old
    fi
    scp -r $connection:/data/ubnext/drupal-files ./files/
    
}

function import_db {
    echo "Importing database"
    # check if the file database.sql exists
    if [ -f ubnext_db.sql ]; then
        echo "File ubnext_db.sql exists"
        scp database.sql $connection:/apps/ubnext/database.sql
        ssh $connection "cd /apps/ubnext && ./restore-database.sh"
        # ask the user if they want to delete the database.sql file
        read -p "Do you want to delete the database.sql file? (y/n) " answer
        if [ $answer == "y" ]; then
            rm database.sql
        fi
    else
        echo "File database.sql does not exist"
        exit 1
    fi
}

function import_files {
    echo "Importing files"
    # check if the directory files exists
    if [ -d files ]; then
        scp -r files $connection:/data/ubnext/drupal-files
    else
        echo "Directory files does not exist"
        exit 1
    fi
}

# check if no arguments are present and if not, display instructions
if [ $# -eq 0 ]; then
    echo "--------------------------------------------------------------------------------------------------------"
    echo "Usage: $0 <environment> <command>:<sub_command (optional)>"
    echo "Valid environments are: ${environments[@]}"
    echo "Valid commands are: ${commands[@]}"
    echo "Valid sub_commands are: ${sub_commands[@]}"
    echo "Ex. $0 lab export:files.............will export the files from the lab environment."
    echo "    $0 lab export:database..........will export the database from the lab environment."
    echo "    $0 lab export...................will export files and database from the lab environment."
    echo "--------------------------------------------------------------------------------------------------------"
    exit 1
fi



#check if the environment is in the environments list
if [[ ! " ${environments[@]} " =~ " ${environment} " ]]; then
    echo "Invalid environment $environment. Valid environments are: ${environments[@]}"
    exit 1
else
    #set the connection string based on the environment
    if [ $environment == "lab" ]; then
        connection=$lab
    elif [ $environment == "staging" ]; then
        connection=$staging
    elif [ $environment == "production" ]; then
        connection=$production
    fi
fi


#if command contains a colon, split the command into two parts and set the second parts a  sub_command
if [[ $command == *":"* ]]; then
    IFS=':' read -r -a command_parts <<< "$command"
    command=${command_parts[0]}
    sub_command=${command_parts[1]}
fi


#check if the command is in the commands list
if [[ " ${commands[@]} " =~ " ${command} " ]]; then
    :
else
    echo "Invalid command $command. Valid commands are: ${commands[@]}"
    exit 1
fi

#check if sub_command length is greater than 0 and if it is in the sub_commands list
if [[ -n $sub_command && ! " ${sub_commands[@]} " =~ " ${sub_command} " ]]; then
    echo "Invalid sub command $sub_command. Valid sub commands are: ${sub_commands[@]}"
    exit 1
fi

if [ $command == "export" ]; then
    if [[ -n $sub_command && $sub_command == "db" ]]; then
        export_db
    elif [[ -n $sub_command && $sub_command == "files" ]]; then
        export_files
    else
        export_db
        export_files
    fi
else
    # import
    # check if environment is 'production'
    if [ $environment == "production" ]; then
        echo "Illegal operation! 'import' not allowed to production environment."
        exit 1
    else
         if [[ -n $sub_command && $sub_command == "db" ]]; then
            import_db
        elif [[ -n $sub_command && $sub_command == "files" ]]; then
            import_files
        else
            import_db
            import_files
        fi
    fi
   
fi

