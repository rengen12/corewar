#!/usr/bin/env ruby

require "oauth2"
UID = "f41131fff1fe03dfcae2d4f396359a71abf3d181e5e3d968eefcafa054581deb"
SECRET = "bcc19b65282d79257c76b310a4281c4f6c45a4e2b08a8ab6c1e9d3366a94623d"
client = OAuth2::Client.new(UID, SECRET, site: "https://api.intra.42.fr")
token = client.client_credentials.get_token

response = token.get("/v2/campus_users/126")
response.status
# => 200
response.parsed
# => {"id"=>126, "user_id"=>126, "campus_id"=>1, "is_primary"=>true}
