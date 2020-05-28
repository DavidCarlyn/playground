import React, { Component } from 'react';
import './App.css';

import SpotifyWebApi from 'spotify-web-api-js';
const spotifyApi = new SpotifyWebApi();
const serverAddress = "192.168.1.107";

class App extends Component {
  constructor(){
    super();
    const params = this.getHashParams();
    const token = params.access_token;
    if (token) {
      spotifyApi.setAccessToken(token);
    }
    this.state = {
      loggedIn: token ? true : false,
      nowPlaying: { name: 'Not Checked', albumArt: '' }
    }
  }
  getHashParams() {
    var hashParams = {};
    var e, r = /([^&;=]+)=?([^&;]*)/g,
        q = window.location.hash.substring(1);
    e = r.exec(q)
    while (e) {
       hashParams[e[1]] = decodeURIComponent(e[2]);
       e = r.exec(q);
    }
    return hashParams;
  }

  pause() {
    spotifyApi.getMyDevices().then(reponse => {
      var id = ""
      reponse.devices.forEach((device) => {
        if (device.is_active) {
          id = device.id;
        }
      })

      console.log(id)

      spotifyApi.pause({device_id : id }).then(reponse => {
        console.log(reponse)
      }).catch(err => {
        console.log(err)
      })
      
    }).catch(err=>{
      console.log(err)
    })

  }

  play() {
    spotifyApi.getMyDevices().then(reponse => {
      var id = ""
      reponse.devices.forEach((device) => {
        if (device.is_active) {
          id = device.id;
        }
      })

      console.log(id)

      spotifyApi.play({device_id : id }).then(reponse => {
        console.log(reponse)
      }).catch(err => {
        console.log(err)
      })
      
    }).catch(err=>{
      console.log(err)
    })
  }

  getNowPlaying(){
    spotifyApi.getMyCurrentPlaybackState()
      .then((response) => {
        this.setState({
          nowPlaying: { 
              name: response.item.name, 
              albumArt: response.item.album.images[0].url
            }
        });
      })
  }

  loadParty() {
    console.log("create_party")
  }

  render() {
    return (
      <div className="App">
        <a href={"http://" + serverAddress + ":8888"}> Login to Spotify </a>
        <a href={"http://" + serverAddress + ":8888/load"}> Load Party </a>
        <div>
          Now Playing: { this.state.nowPlaying.name }
        </div>
        <div>
          <img src={this.state.nowPlaying.albumArt} style={{ height: 150 }}/>
        </div>
        { this.state.loggedIn &&
          <div>
          <button onClick={() => this.getNowPlaying()}>
            Check Now Playing
          </button>
          <button onClick={() => this.pause()}>
            Click to pause
          </button>
          <button onClick={() => this.play()}>
            Click to play
          </button>
          </div>
        }
      </div>
    );
  }
}

export default App;
