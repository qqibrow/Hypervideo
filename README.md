Hypervideo is a displayed video stream that contains embedded, user-clickable anchors allowing navigation between video and other hypermedia elements.Hypervideo thus combines video with a non linear information structure, allowing a user to make choices based on the content of the video and the user's interests.

The whole project consists of two parts: a hyper linking tool for video and a video player to interactive with hypervideos. One hyperlink should be a connection of 2 videos. One is primary video, which users will be watching; the other is secondary video, which is the link target of a hyperlink. Therefore, in order to create one hyperlink, the tool should load in these two videos, create a area in the primary video and then save it into file. As to the hyperlink video player, it should not only play the audio and images, but also load in the bounded hyperlink file and show the user-clickable area in specific frames during playing. Once user click that area, it will automatically play the linked target video from a specific frame. This target video can also have hyperlinks. So the whole thing is like hypertext on the website. your click one, jump to another webpage and can click new ones.

This project is implemented in C++, using Qt library. Qt is more than a UI creator, but a event-driven programming library. I am still studying its "slot and signal" mechanism, similar to that in Boost. It is really amazing and powerful.

Currently, it is still under testing for better performance. The beta version will be comming soon.

