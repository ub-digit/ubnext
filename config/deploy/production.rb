# Simple Role Syntax
# ==================
# Supports bulk-adding hosts to roles, the primary server in each group
# is considered to be the first unless any hosts have the primary
# property set.  Don't declare `role :all`, it's a meta role.

# role :app, %w{deploy@example.com}
# role :web, %w{deploy@example.com}
# role :db,  %w{deploy@example.com}


# Extended Server Syntax
# ======================
# This can be used to drop a more detailed server definition into the
# server list. The second argument is a, or duck-types, Hash and is
# used to set extended properties on the server.

# server 'example.com', user: 'deploy', roles: %w{web app}, my_property: :my_value
server 'beta.ub.gu.se', user: 'drupal-deploy', roles: %w{app},
  ubn_conf: {
    ubn_settings_solr_host: 'localhost',
    slate_cache_enabled: 1,
    ubn_terms_cache: 1
  }

set :deploy_to, '/var/www/drupal/production'

# Set release tag
set :branch, 'release-2019.05-004'



# Drupal deploy
set :drupal_data_permit_write, false

namespace :deploy do
  before :starting, :set_command_map_paths do
    puts "You are about to deploy tag '#{fetch(:branch)}' to the production site, do you wish to proceed? (y/n)"
    ask(:confirmation)
    answer = fetch(:confirmation)
    if answer == 'y'
      #proceed with deploy as user apparently would like to...
      puts "Proceeding with deploy of tag '#{fetch(:branch)}' to production"
    else
      puts 'Aborting deploy!'
      #exiting deploy for all answers but 'y'
      exit
    end
  end
end

# Custom SSH Options
# ==================
# You may pass any option but keep in mind that net/ssh understands a
# limited set of options, consult[net/ssh documentation](http://net-ssh.github.io/net-ssh/classes/Net/SSH.html#method-c-start).
#
# Global options
# --------------
#  set :ssh_options, {
#    keys: %w(/home/rlisowski/.ssh/id_rsa),
#    forward_agent: false,
#    auth_methods: %w(password)
#  }
#
# And/or per server (overrides global)
# ------------------------------------
# server 'example.com',
#   user: 'user_name',
#   roles: %w{web app},
#   ssh_options: {
#     user: 'user_name', # overrides user setting above
#     keys: %w(/home/user_name/.ssh/id_rsa),
#     forward_agent: false,
#     auth_methods: %w(publickey password)
#     # password: 'please use keys'
#   }
