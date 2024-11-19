# Ubnext playbooks

## Installation
To install ub-ansible-deploy role and other dependencies required by this playbook run `ansible-galaxy install -r requirements.yml`
To update dependencies run the same command with the -f flag to force reinstalltion.

## Deployment
- Save vault password in `.vault_password`
- Run `ansible-playbook -i inventory/<host>.yml --vault-password-file .vault_password deploy.yml` replacing \<host\> with host alias name, for example `lab`.

(The -C flag can be used to run the playbook without performing and changes on the target server.)

## ./run-playbook.sh

Helper script for running playbook. To use, run `./run-playbook.sh <playbook> <host>`.
