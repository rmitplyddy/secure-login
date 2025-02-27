// ** Require Re-authentication for Sensitive Features **
// In order to mitigate CSRF and session hijacking, it's important to require
// the current credentials for an account before updating sensitive account 
// information such as the user's password or email address -- or before 
// sensitive transactions, such as shipping a purchase to a new address. 
// Without this countermeasure, an attacker may be able to execute sensitive 
// transactions through a CSRF or XSS attack without needing to know the user's 
// current credentials. Additionally, an attacker may get temporary physical 
// access to a user's browser or steal their session ID to take over the user's 
// session.