OpenSSH_8.1p1, LibreSSL 2.7.3
debug1: Reading configuration data /etc/ssh/ssh_config
debug1: /etc/ssh/ssh_config line 47: Applying options for *
debug1: Connecting to sandbox.ejudge.ru port 22.
debug1: Connection established.
debug1: identity file /Users/rinatgorbachev/.ssh/id_rsa type 0
debug1: identity file /Users/rinatgorbachev/.ssh/id_rsa-cert type -1
debug1: identity file /Users/rinatgorbachev/.ssh/id_dsa type -1
debug1: identity file /Users/rinatgorbachev/.ssh/id_dsa-cert type -1
debug1: identity file /Users/rinatgorbachev/.ssh/id_ecdsa type -1
debug1: identity file /Users/rinatgorbachev/.ssh/id_ecdsa-cert type -1
debug1: identity file /Users/rinatgorbachev/.ssh/id_ed25519 type -1
debug1: identity file /Users/rinatgorbachev/.ssh/id_ed25519-cert type -1
debug1: identity file /Users/rinatgorbachev/.ssh/id_xmss type -1
debug1: identity file /Users/rinatgorbachev/.ssh/id_xmss-cert type -1
debug1: Local version string SSH-2.0-OpenSSH_8.1
debug1: Remote protocol version 2.0, remote software version OpenSSH_8.4
debug1: match: OpenSSH_8.4 pat OpenSSH* compat 0x04000000
debug1: Authenticating to sandbox.ejudge.ru:22 as 'bpmi19290'
debug1: SSH2_MSG_KEXINIT sent
debug1: SSH2_MSG_KEXINIT received
debug1: kex: algorithm: curve25519-sha256
debug1: kex: host key algorithm: ecdsa-sha2-nistp256
debug1: kex: server->client cipher: chacha20-poly1305@openssh.com MAC: <implicit> compression: none
debug1: kex: client->server cipher: chacha20-poly1305@openssh.com MAC: <implicit> compression: none
debug1: expecting SSH2_MSG_KEX_ECDH_REPLY
debug1: Server host key: ecdsa-sha2-nistp256 SHA256:kCUkPfYBgbfAQGkqkJCb1MQAe3re67mdSoh7KDEIsPg
debug1: Host 'sandbox.ejudge.ru' is known and matches the ECDSA host key.
debug1: Found key in /Users/rinatgorbachev/.ssh/known_hosts:1
debug1: rekey out after 134217728 blocks
debug1: SSH2_MSG_NEWKEYS sent
debug1: expecting SSH2_MSG_NEWKEYS
debug1: SSH2_MSG_NEWKEYS received
debug1: rekey in after 134217728 blocks
debug1: Will attempt key: /Users/rinatgorbachev/.ssh/id_rsa RSA SHA256:fqEo+UoK4R55nlo/GgSbVEhUMTevxsbWkM1xS7YhF8g
debug1: Will attempt key: /Users/rinatgorbachev/.ssh/id_dsa 
debug1: Will attempt key: /Users/rinatgorbachev/.ssh/id_ecdsa 
debug1: Will attempt key: /Users/rinatgorbachev/.ssh/id_ed25519 
debug1: Will attempt key: /Users/rinatgorbachev/.ssh/id_xmss 
debug1: SSH2_MSG_EXT_INFO received
debug1: kex_input_ext_info: server-sig-algs=<ssh-ed25519,sk-ssh-ed25519@openssh.com,ssh-rsa,rsa-sha2-256,rsa-sha2-512,ssh-dss,ecdsa-sha2-nistp256,ecdsa-sha2-nistp384,ecdsa-sha2-nistp521,sk-ecdsa-sha2-nistp256@openssh.com,webauthn-sk-ecdsa-sha2-nistp256@openssh.com>
debug1: SSH2_MSG_SERVICE_ACCEPT received
debug1: Authentications that can continue: publickey,gssapi-keyex,gssapi-with-mic,password
debug1: Next authentication method: publickey
debug1: Offering public key: /Users/rinatgorbachev/.ssh/id_rsa RSA SHA256:fqEo+UoK4R55nlo/GgSbVEhUMTevxsbWkM1xS7YhF8g
debug1: Server accepts key: /Users/rinatgorbachev/.ssh/id_rsa RSA SHA256:fqEo+UoK4R55nlo/GgSbVEhUMTevxsbWkM1xS7YhF8g
debug1: Authentication succeeded (publickey).
Authenticated to sandbox.ejudge.ru ([3.250.144.49]:22).
debug1: channel 0: new [client-session]
debug1: Requesting no-more-sessions@openssh.com
debug1: Entering interactive session.
debug1: pledge: network
debug1: channel 0: free: client-session, nchannels 1
debug1: fd 2 clearing O_NONBLOCK
Killed by signal 2.