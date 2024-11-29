#!/bin/bash
set -x
ansible-playbook --vault-password-file .vault_password -i inventory/$2.yml $1.yml
