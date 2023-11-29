
# Load DSL and Setup Up Stages
require 'capistrano/setup'

# Includes default deployment tasks
require 'capistrano/deploy'

# Include git
require "capistrano/scm/git"
install_plugin Capistrano::SCM::Git

# Composer is needed to install drush on the server
require 'capistrano/composer'

# Npm/nodejs is needed for grunt etc
require 'capistrano/npm'

# Require erb for settings files templating purposes
require 'capistrano/capistrano_plugin_template'

# Hmmmm??
require_relative 'lib/capistrano/capistrano_drupal'

# Includes tasks from other gems included in your Gemfile
#
# For documentation on these, see for example:
#
#   https://github.com/capistrano/rvm
#   https://github.com/capistrano/rbenv
#   https://github.com/capistrano/chruby
#   https://github.com/capistrano/bundler
#   https://github.com/capistrano/rails
#
# require 'capistrano/rvm'
# require 'capistrano/rbenv'
# require 'capistrano/chruby'
# require 'capistrano/bundler'
# require 'capistrano/rails/assets'
# require 'capistrano/rails/migrations'

# Loads custom tasks from `lib/capistrano/tasks' if you have any defined.
Dir.glob('lib/capistrano/tasks/*.rake').each { |r| import r }
