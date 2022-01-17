# Twitter

## Correction scale 

<ul>
  <li>const ref</li>
<li>move semantics</li>
<li>modern data structures</li>
<li>modern algorithms</li>
<li>smart pointers</li>
<li>template</li>
<li>Regex</li>
<li>DLL</li>
<li>Logging</li>
  </ul>

## Minimum scale
<ol>
  <li>At startup, a user is given the option to log in to their account or they can create an account. Login / registration involves entering the username.</li>
  
Warning: username must be unique!

  <li>The main menu displays the following options (features):
    <ol>
      <li><strong>Post</strong>: the user can make a text post of up to 140 characters;</li>
      <li><strong>Personal Profile</strong>: The user can see the history of his posts</li>
      <li><strong>Follow function</strong>: user can "make friends" with other users. This way you can build the social graph of the platform.</li>
      <li><strong>Feed</strong>: viewing posts. One post at a time will be displayed - see details below. The following options will be posted below:
      <ul>
        <li>Like or Dislike - the user can like / dislike and withdraw their reaction</li>
        <li>Comment - the user can write a comment, and the list of comments will be updated</li>
        <li>See all comments</li>
        <li>Retweet - the user will be able to enter a preface to his post</li>
        <li>Go to referenced tweet - if the post is a retweet, it will be possible to access the original post</li>
        <li>Next / previous post</li>
        <li>Back to main menu</li>
      </ul></li>
      <li><strong>Keyword Search</strong>: The user enters a multi-keyword query and displays posts that contain at least one searched keyword - see Inverted Index.</li>
      
Warning: Try to prioritize the latest results.
      <li><strong>User Search</strong>: The user enters a user name as a query and the list of results is displayed. A result does not have to be identical to the query, but similar values can be displayed. To compare strings implement distance Levenshtein.</li></li></ol></ol>
      
## Advanced project components

<ol>
  <li><strong>GUI</strong> - graphical interface for all the functionalities in the minimum scale of the client application.</li>
  <li><strong>Networking</strong> - the communication between client and server applications to be done using Sockets </li>
  <li><strong>Database</strong> - the data used by the server will be manipulated using a database </li>
</ol>

  ## Teammates
  
  [Sdraila Valentin](#)
  
  [Similie Vlad-Gabriel](#)
  
  [Sulu David](#)
  
  <details>
  <summary><b>📷 Images 📷</b></summary>
  </br>
  
  [video presentation](https://github.com/DenisaXXIV/Twitter/blob/master/util/Prezentare-Twitter.mkv)
  
  </br>

  <img src="https://github.com/DenisaXXIV/Twitter/blob/master/util/intro.png" width="350"/>

  <img src="https://github.com/DenisaXXIV/Twitter/blob/master/util/register.png" width="350"/>
</br>
</br>
</br>
  <img src="https://github.com/DenisaXXIV/Twitter/blob/master/util/feed.png" width="350"/>

  <img src="https://github.com/DenisaXXIV/Twitter/blob/master/util/add_post.png" width="350"/>
  </br>
</br>
</br>
  <img src="https://github.com/DenisaXXIV/Twitter/blob/master/util/profile.png" width="350"/>

  </details>
