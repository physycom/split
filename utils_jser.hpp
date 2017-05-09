#ifndef PHYSYCOM_UTILS_JSER_HPP
#define PHYSYCOM_UTILS_JSER_HPP

#include <vector>

// Utility class to automatize
// the conversion from and to JSON object

// To use it you must provide a valid
// json type (e.g using using)

namespace physycom{
	
	// (De)Serialize JSON into class
	template<class T>
	std::vector<T> deserialize(const json &j){
	  std::vector<T> trip(0);
	  T point;
	  if( j.is_array() ){
	    for(const auto &r : j.array_range()){
	      trip.emplace_back(r);
	    }
	  }
	  else if ( j.is_object() ){
	    for(const auto &r : j.object_range()){
	      trip.emplace_back(r.value());
	    }
	  }
	  return trip;
	}
	
	template<class T>
	json serialize(const std::vector<T> &vec, char mode = 'a'){
	  json j;
	  json r;
	  if ( mode == 'a'){     // array
	    j = json::array();
	    for(const auto &r : vec){
	      j.add(r.to_json());
	    } 
	  }
	  else if ( mode ==  'o'){
	    size_t cnt = 0;
	    std::string prefix = "record_";
	    for(const auto &r : vec){
	      std::stringstream ss;
	      ss << prefix << std::setw(5) << std::setfill('0') << std::endl;
	      j[ss.str()] = r.to_json();
	    }
	  }
	  return j;
	}
	

}   // end namespace physycom

#endif // PHYSYCOM_UTILS_JSER_HPP
