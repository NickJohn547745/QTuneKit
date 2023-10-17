#include "playbackmonitor.h"

PlaybackMonitor::PlaybackMonitor()
{

}
class PlaybackMonitor {
  activate() {
    this.isActive = true, this.startMonitor();
  }
  deactivate() {
    this.isActive = false, this.clearMonitor();
  }
  clearMonitor() {
    this.isMonitoring && (this.watchers.forEach(e => e.stopMonitor()), this.isMonitoring = false);
  }
  shouldMonitor() {
    return this.isActive;
  }
  startMonitor() {
    this.shouldMonitor() && (this.watchers.forEach(e => e.startMonitor()), this.isMonitoring = true);
  }
  handleMediaItemChange() {
    this.isActive && (this.clearMonitor(), this.shouldMonitor() && this.startMonitor());
  }
  constructor(e) {
    this.isActive = false, this.isMonitoring = false, this.watchers = [], this.handlePlaybackThreshold = this.handlePlaybackThreshold.bind(this), this.playbackController = e.controller, this.dispatcher = e.services.dispatcher, this.dispatcher.subscribe(ss.nowPlayingItemDidChange, this.handleMediaItemChange), this.apiManager = e.services.apiManager;
  }
}
